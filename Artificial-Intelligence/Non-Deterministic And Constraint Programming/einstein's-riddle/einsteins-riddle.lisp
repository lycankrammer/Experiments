;;;; Common Lisp file:
;;;;                 einstein's-riddle/einsteins-riddle.lisp
;;;;
;;;; Einstein's Riddle Puzzle using non-deterministic programming

;;;==========================================
;;; Package definition
;;;==========================================
(eval-when (:compile-toplevel :load-toplevel)
  (require :screamer))

(defpackage einsteins-riddle
  (:shadowing-import-from #:screamer
                          #:defun
                          #:multiple-value-bind
                          #:y-or-n-p)
  (:use #:common-lisp #:screamer))

(in-package einsteins-riddle)

;;; Example: "The Einstein's Riddle".
;;;
;;; There are five houses in a row, each of different color.
;;;
;;; Each has an owner of a different nationality.
;;;
;;; Each owner has a unique favorite drink, type of cigarette, and a pet.
;;;
;;;    1. The Brit lives in the red house
;;;    2. The Swede keeps dogs as pets
;;;    3. The Dane drinks tea
;;;    4. The green house is on the left of the white house
;;;    5. The green house's owner drinks coffee
;;;    6. The person who smokes Pall Mall rears birds
;;;    7. The owner of the yellow house smokes Dunhill
;;;    8. The man living in the center house drinks milk
;;;    9. The Norwegian lives in the first house
;;;   10. The person who smokes Marlboro lives next to the one who keeps cats
;;;   11. The person who keeps horses lives next to the person who smokes Dunhill
;;;   12. The person who smokes Winfield drinks beer
;;;   13. The German smokes Rothmans
;;;   14. The Norwegian lives next to the blue house
;;;   15. The person who smokes Marlboro has a neighbor who drinks water
;;;
;;; Question: Who owns the fish?

;;; Description  Assert a fact
;;;
;;; Parameter:
;;;     - bool  a boolean value
;;;
;;; If bool is false, calls screamer:fail, that backtracks to the most recent
;;; choice-point. Otherwise, just return NIL.
;;;
(defun fact! (bool)
  (unless bool
    (fail)))

;;; Description  Assert a contradiction
;;;
;;; Parameter:
;;;     - bool  a boolean value
;;;
;;; If bool is true, calls screamer:fail, that backtracks to the most recent
;;; choice-point. Otherwise, just return NIL.
;;;
(defun not! (bool)
  (when bool
    (fail)))

;;; Description  Assert that the two values are the same
;;;
;;; Parameters:
;;;     - fact1  a boolean value
;;;     - fact2  a boolean value
;;;
;;; If both facts have different boolean values, calls screamer:fail, that
;;; backtracks to the most recent choice-point. Otherwise, just return T.
;;;
(defun and! (fact1 fact2)
  (or (and fact1 fact2)
      (and (not fact1) (not fact2))
      (fail)))

;;; Description  The target houses
;;;
(defstruct house
  color
  owner
  pet
  drink
  cigarette
  position)

;;; Description   Macro that  creates  the  functions  that  chooses  an item
;;;               of one of the slots in struct 'house' non-deterministically.
;;;               The function Guaratees that it  does  not produces  one  of
;;;               items already in one of the houses in the parameter 'others'.
;;;
;;; Parameters:
;;;     - slot     the given slot of the struct 'house'
;;;     - name     the name of the created function
;;;     - options  the possible options of the given slot
;;;
;;; Produces non-deterministically one possible item for a house that is not
;;; an item already in 'others'.
;;;
(macrolet ((def (slot name &rest options)
             (assert (= 5 (length options)))
             `(defun ,name (&optional (others nil))
                (let ((this (either ,@options)))
                  (not! (member this others
                                :key #',(intern (format nil "HOUSE-~A" slot))
                                :test #'eq))
                  this))))

  (def color a-color :red :green :white :yellow :blue)
  (def owner an-owner :brit :swede :dane :norwegian :german)
  (def pet a-pet :dog :bird :cat :horse :fish)
  (def drink a-drink :tea :coffee :milk :beer :water)
  (def cigarette a-cigarette :pallmall :dunhill :marlboro :winfield :rothmans))

;;; Description  Generator for houses. Immediately checks facts about the
;;;              house.
;;;
;;; We could optimize here in two ways:
;;;
;;; 1. Order the assertions so that we assert as much as possible  before
;;;    entering a choice-point. For example, rule #9 would be better done
;;;    immediately after generating the owner.
;;;
;;; 2. Change the property generators to  accept  a  required value. Then
;;;    instead of
;;;      (AN-OWNER OTHERS)
;;;    we would have
;;;      (AN-OWNER OTHERS (WHEN (ZEROP POSITION) :NORWEGIAN))
;;;
;;; but even keeping the order of assertions the same as in the puzzle we
;;; win big by asserting as many  of them  as possible  before generating
;;; new house properties.
;;;
;;; Paramters:
;;;     - position  number on the street [0-4]
;;;
;;; Returns:
;;;     - a new house with its slots filled in by the correct properties
;;;
(defun a-house (position &rest others)
  (let ((color (a-color others))
        (owner (an-owner others)))
    (and! (eq :brit owner) (eq :red color))                  ; Rule 1
    (let ((pet (a-pet others)))
      (and! (eq :swede owner) (eq :dog pet))                 ; Rule 2
      (let ((drink (a-drink others)))
        (and! (eq :dane owner) (eq :tea drink))              ; Rule 3
        (let ((cigarette (a-cigarette others)))
          (and! (eq :green color) (eq :coffee drink))        ; Rule 5
          (and! (eq :pallmall cigarette) (eq :bird pet))     ; Rule 6
          (and! (eq :yellow color) (eq :dunhill cigarette))  ; Rule 7
          (and! (= position 2) (eq :milk drink))             ; Rule 8
          (and! (= position 0) (eq :norwegian owner))        ; Rule 9
          (and! (eq :winfield cigarette) (eq :beer drink))   ; Rule 12
          (and! (eq :german owner) (eq :rothmans cigarette)) ; Rule 13
          ;; Passed all necessary assertions
          (make-house
           :color color
           :owner owner
           :pet pet
           :drink drink
           :cigarette cigarette
           :position position))))))

;;; Description  Pass already created houses to generators so that
;;;              we can get unique properties.
;;;
(defun a-street ()
  (let* ((a (a-house 0))
         (b (a-house 1 a))
         (c (a-house 2 a b))
         (d (a-house 3 a b c))
         (e (a-house 4 a b c d)))
    (list a b c d e)))

;;; Description  An anaproric macro for picking a house based on a property.
;;;              Captures HOUSES.
;;;
;;; Parameters:
;;;     - key    a particular slot key. Eg, :color
;;;     - value  a particular value for that key. Eg, :red
;;;
;;; Returns:
;;;     - a house with that particular key-value
;;;
(defmacro house (key value)
  `(or (car (member ,value houses
                    :key #',(intern (format nil "HOUSE-~A" key))
                    :test #'eq))
       (error "[EINSTEIN'S-RIDDLE ERROR]: No ~S ~S" ,key ,value)))

;;; Description  Solves the riddle: generate the street, then assert relationships
;;;              between the houses.
;;;
(defun solve-riddle (&optional (all t))
  (let ((houses (a-street)))
    (let ((left-of-white (1- (house-position (house :color :white))))
          (green (house :color :green)))
      (fact! (= (house-position green) left-of-white)))              ; Rule 4
    (let ((marlboro (house-position (house :cigarette :marlboro)))
          (cat (house-position (house :pet :cat))))
      (fact! (= 1 (abs (- cat marlboro))))                           ; Rule 10
      (let ((horses (house-position (house :pet :horse)))
            (dunhill (house-position (house :cigarette :dunhill))))
        (fact! (= 1 (abs (- horses dunhill)))))                      ; Rule 11
      (let ((norwegian (house-position (house :owner :norwegian)))
            (blue (house-position (house :color :blue))))
        (fact! (= 1 (abs (- norwegian blue)))))                      ; Rule 14
      (let ((water (house-position (house :drink :water))))
        (fact! (= 1 (abs (- marlboro water))))))                     ; Rule 15
    (if all
        houses
        (house :pet :fish))))

#+nil
(time (one-value (solve-riddle)))



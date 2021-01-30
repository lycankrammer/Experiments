;;;; Common Lisp file:
;;;;                 zebras-puzzle.lisp
;;;;
;;;; Zebra Puzzle using Logic Variables

(eval-when (:compile-toplevel :load-toplevel)
  (require :screamer))

;;;======================================
;;; Package definition
;;;======================================
(defpackage zebra-puzzle
  (:shadowing-import-from #:screamer
                          #:defun
                          #:multiple-value-bind
                          #:y-or-n-p)
  (:use #:common-lisp #:screamer))

(in-package zebra-puzzle)

;;; Example: "The Zebra Puzzle"
;;;
;;; Classic riddle popularly attributed to Lewis Carrol. (Essentially the
;;; same as "The Einstein's Riddle".)
;;;
;;; This solution, contributed by Stephan Frank, uses the constraint
;;; propagation features of Screamer.
;;;
;;; Five men with different nationalities live in the first five houses of a
;;; street.  They  practice  distinct  professions, and  each  of them has a
;;; favourite  animal and a favourite drink, all of them different. The five
;;; houses are painted in different colours.
;;;
;;;    1. The Englishman lives in a red house.
;;;    2. The Spaniard owns a dog.
;;;    3. The Japanese is a painter.
;;;    4. The Italian drinks tea.
;;;    5. The Norwegian lives in the first house on the left.
;;;    6. The owner of the green house drinks coffee.
;;;    7. The green house is on the right of the white one.
;;;    8. The sculptor breeds snails.
;;;    9. The diplomat lives in the yellow house.
;;;   10. Milk is drunk in the middle house.
;;;   11. The Norwegian's house is next to the blue one.
;;;   12. The violinist drinks fruit juice.
;;;   13. The fox is in a house next to that of the doctor.
;;;   14. The horse is in a house next to that of the diplomat.
;;;
;;; Question: Who owns a Zebra, and who drinks water?

;;; Description  Binds names in VAR-LIST to integer variables constrained in the
;;;              range [min, max]
;;;
;;; Parameters:
;;;     - min       the minimum value of interval
;;;     - max       the maximum value of interval
;;;     - var-list  a list of names to bind to the contrained variables
;;;     - body      the body to be executed
;;;
(defmacro let-integers-betweenv (((min max) var-list) body)
  `(let ,(loop :for i :in var-list
               :collect (list i `(an-integer-betweenv ,min ,max)))
     ,body))

;;; Description  Tests if all variables in LIST are different. This is functionally
;;;              the same as (apply #'/=v list), but faster.
;;;
;;; Parameter:
;;;     - list   a list to be tested
;;;
;;; Returns:
;;;     - t     if all values in list are different
;;;     - nil   otherwise
;;;
(defun all-differentv (list)
  (labels ((all-different (x xs)
             (if (null xs)
                 t
                 (andv (notv (=v x (car xs)))
                       (all-different x (cdr xs))
                       (all-different (car xs) (cdr xs))))))
    (all-different (car list) (cdr list))))

;;; Constraint Model
;;;
;;; Houses are identified by integers from 1 to 5.
;;;
;;; We first bind logic variables taking values in that range in
;;; LET-INTEGERS-BETWEENV for all properties. We group them  and
;;; assert that  every  values  is  unique  in its  group  using
;;; ALL-DIFFERENTV.
;;;
;;; We create three mode logic variables to represent  distances
;;; between certain houses.
;;;
;;; We assert the constraints stated in the riddle.
;;;
;;; Finally,  we   ask  screamer  to  provide  a  solution  that
;;; satisfies all given constraints.
;;;
(defun solve-zebra-problem ()
  (let-integers-betweenv ((1 5)
                          (English Spaniard Japanese Italian Norwegian
                                   Red Green White Yellow Blue
                                   Painter Sculptor Diplomat Violinist Doctor
                                   Dog Snails Fox Horse Zebra
                                   Tea Coffee Milk Juice Water))
                         (let ((nationality (list English Spaniard Japanese Italian Norwegian))
                               (color (list Red Green White Yellow Blue))
                               (profession (list Painter Sculptor Diplomat Violinist Doctor))
                               (pet (list Dog Snails Fox Horse Zebra))
                               (drink (list Tea Coffee Milk Juice Water)))
                           ;; The values in each list are exclusive
                           (assert! (all-differentv nationality))
                           (assert! (all-differentv color))
                           (assert! (all-differentv profession))
                           (assert! (all-differentv pet))
                           (assert! (all-differentv drink))
                           ;; The actual constraints from the problem description
                           (assert! (=v English Red))
                           (assert! (=v Spaniard Dog))
                           (assert! (=v Japanese Painter))
                           (assert! (=v Italian Tea))
                           (assert! (=v Norwegian 1))
                           (assert! (=v Green Coffee))
                           (assert! (=v Green (+v White 1)))
                           (assert! (=v Sculptor Snails))
                           (assert! (=v Diplomat Yellow))
                           (assert! (=v Milk 3))
                           (assert! (=v (-v Norwegian Blue) (a-member-ofv (list -1 1))))
                           (assert! (=v Violinist Juice))
                           (assert! (=v (-v Doctor Fox) (a-member-ofv (list -1 1))))
                           (assert! (=v (-v Diplomat Horse) (a-member-ofv (list -1 1))))
                           ;; Force a solution
                           (let ((result
                                   (one-value
                                       ;; Feed all the primary values into the solution: we don't
                                       ;; want any uncertainty to remain  regarding these.  If we
                                       ;; merely fed  in NATIONALITY, ZEBRA, and WATER,  we might
                                       ;; return false results where some of the constraints were
                                       ;; not fully checked because Eg. PROFESSION wasn't solved.
                                       (solution (list nationality pet drink color profession)
                                                 (static-ordering #'linear-force)))))
                             ;; Human-readable labels: results we have back are integers identifying
                             ;; the houses. Map back to nationalities.
                             (destructuring-bind (nationality pet drink &rest rest) result
                               (declare (ignore rest))
                               (let ((names (vector "Brit" "Spaniard" "Japanese" "Italian" "Norwegian")))
                                 (format t "The ~a owns the zebra.~%"
                                         (aref names (position (first pet) nationality)))
                                 (format t "The ~a drinks water.~%"
                                         (aref names (position (first drink) nationality)))))))))

#+nil
(time (one-value (solve-zebra-problem)))

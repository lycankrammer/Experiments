;;;; Common Lisp file:
;;;;                 package.lisp
;;;;
;;;; Package for L-cl-utils

(in-package :cl-user)

(defpackage+-1:defpackage+ #:L-cl-utils
  (:nicknames #:L-cl-u #:Lclu)
  (:use #:common-lisp)

  ;; Third-parties (defpackage-plus)
  (:inherit-from #:alexandria
                 #:appendf          ; append lists to a PLACE by SETFing and NOT by changing CONS cells
                 #:clamp            ; clamps a number within a range [min, max]
                 #:copy-hash-table  ; copy a hash table
                 #:deletef          ; deletes item from place by modifying it
                 #:format-symbol    ; constructs a new symbol using CL format system
                 #:iota             ; creates a list of numbers
                 #:lerp             ; interpolate between two numbers linearly
                 #:make-keyword     ; intern a symbol into the keyword package
                 #:shuffle          ; shuffles a sequence randomly
                 #:symbolicate      ; creates a new symbol by concatenating the specified string designators (character, string, or symbol)
                 #:when-let         ; a LET that only executes the body of the form if all the binds are not NIL
                 #:with-gensyms     ; creates gensyms
                 #:define-constant  ; use it instenad of DEFCONSTANT
                 #:once-only)       ; generates code that evaluates certain macro arguments once only and in a particular order

  (:inherit-from #:serapeum
                 #:defplace         ; define NAME and (SETF NAME) in one go
                 #:dict             ; populates a hash-table from key-value pairs
                 #:href             ; accesses values from a hash table (Useful with nested hash-tables)
                 #:merge-tables     ; merge two hash tables
                 #:mvlet            ; multiple value bind for many lists of bindings (instead of just one)
                 #:partition        ; partitions a sequence according to a predicate
                 #:bestn)           ; partial sorting

  ;; Exported custom macros
  (:export
   #:while                          ; while loop utility
   #:define-printer                 ; custom object printer
   #:when-found                     ; when found var with a lookup function (key found in a hash-table, for example), executes the body
   #:unless-found                   ; unless version of when-found
   #:if-found)                      ; if version of when-found
  ;; Exported custom constants
  (:export
   #:+seconds/minute+
   #:+minutes/hour+
   #:+hours/day+
   #:+seconds/hour+
   #:+seconds/day+
   #:+minutes/day+
   #:+days/week+
   #:+hours/week+
   #:+minutes/week+
   #:+seconds/week+
   #:+day-names+
   #:+day-names-short+
   #:+month-names+
   #:+month-names-short+)
  ;; Exported custom types
  (:export
   #:byte8
   #:ubyte8
   #:byte16
   #:ubyte16
   #:byte32
   #:ubyte32)
  ;; Exported character predicates
  (:export
   #:ascii-char-p                   ; returns true if argument is part of ascii set, false otherwise
   #:ascii-lowercase-p
   #:ascii-uppercase-p
   #:ascii-letter-p
   #:ascii-number-p
   #:ascii-alphanum-p))

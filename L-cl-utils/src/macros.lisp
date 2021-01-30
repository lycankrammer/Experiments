;;;; Common Lisp file:
;;;;                 macros.lisp
;;;;
;;;; Implements utility macros

(in-package :L-cl-utils)

(defmacro while (predicate &body body)
  `(loop :while ,predicate
         :do ,@body))

(defmacro define-printer ((obj stream &key (type t) identity) &body body)
  `(defmethod print-object ((,obj ,obj) ,stream)
     (print-unreadable-object (,obj ,stream :type ,type :identity ,identity)
       ,@body)))

;;; The following macros takes a variable name, a multiple  function that returns
;;; multiple values like GETHASH and executes BODY if the LOOKUP function returns
;;; T (or NIL) binding  VAR (for WHEN-FOUND)  to the first  argument returned  by
;;; the LOOKUP function. The IF-FOUND macro works in a similar manner.

(defmacro when-found ((var lookup) &body body)
  (with-gensyms (found)
    `(multiple-value-bind (,var ,found) ,lookup
       (when ,found
         ,@body))))

(defmacro unless-found ((lookup) &body body)
  (with-gensyms (found placeholder)
    `(multiple-value-bind (,placeholder ,found) ,lookup
       (declare (ignore ,placeholder))
       (unless ,found
         ,@body))))

(defmacro if-found ((var lookup) then else)
  (with-gensyms (found)
    `(multiple-value-bind (,var ,found) ,lookup
       (if ,found
           ,then
           ,else))))

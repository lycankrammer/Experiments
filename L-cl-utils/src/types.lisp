;;;; Common Lisp file:
;;;;                 types.lisp
;;;;
;;;; Some common type definitions

(in-package :L-cl-utils)

(deftype byte8 () '(signed-byte 8))
(deftype ubyte8 () '(unsigned-byte 8))
(deftype byte16 () '(signed-byte 16))
(deftype ubyte16 () '(unsigned-byte 16))
(deftype byte32 () '(signed-byte 32))
(deftype ubyte32 () '(unsigned-byte 32))

;;;; ASD file:
;;;;          L-cl-utils.asd
;;;;
;;;; ASDF for L-cl-utils

(asdf:defsystem #:L-cl-utils
  :description "Common Lisp utilities"
  :author ("")
  :license "MIT"
  :version "0.1.0"
  :depends-on (#:alexandria
               #:serapeum
               #:defpackage-plus)
  :pathname "src/"
  :serial t
  :components ((:file "package")
               (:file "macros")
               (:file "constants")
               (:file "types")
               (:file "character")))


(cl:in-package :asdf)

(defsystem "display_test-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Pub_class_distance" :depends-on ("_package_Pub_class_distance"))
    (:file "_package_Pub_class_distance" :depends-on ("_package"))
  ))
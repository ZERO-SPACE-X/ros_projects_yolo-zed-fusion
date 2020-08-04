;; Auto-generated. Do not edit!


(when (boundp 'display_test::Pub_class_distance)
  (if (not (find-package "DISPLAY_TEST"))
    (make-package "DISPLAY_TEST"))
  (shadow 'Pub_class_distance (find-package "DISPLAY_TEST")))
(unless (find-package "DISPLAY_TEST::PUB_CLASS_DISTANCE")
  (make-package "DISPLAY_TEST::PUB_CLASS_DISTANCE"))

(in-package "ROS")
;;//! \htmlinclude Pub_class_distance.msg.html


(defclass display_test::Pub_class_distance
  :super ros::object
  :slots (_classes _distance _x_center _y_center _id ))

(defmethod display_test::Pub_class_distance
  (:init
   (&key
    ((:classes __classes) (let (r) (dotimes (i 0) (push "" r)) r))
    ((:distance __distance) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:x_center __x_center) (make-array 0 :initial-element 0 :element-type :integer))
    ((:y_center __y_center) (make-array 0 :initial-element 0 :element-type :integer))
    ((:id __id) (make-array 0 :initial-element 0 :element-type :integer))
    )
   (send-super :init)
   (setq _classes __classes)
   (setq _distance __distance)
   (setq _x_center __x_center)
   (setq _y_center __y_center)
   (setq _id __id)
   self)
  (:classes
   (&optional __classes)
   (if __classes (setq _classes __classes)) _classes)
  (:distance
   (&optional __distance)
   (if __distance (setq _distance __distance)) _distance)
  (:x_center
   (&optional __x_center)
   (if __x_center (setq _x_center __x_center)) _x_center)
  (:y_center
   (&optional __y_center)
   (if __y_center (setq _y_center __y_center)) _y_center)
  (:id
   (&optional __id)
   (if __id (setq _id __id)) _id)
  (:serialization-length
   ()
   (+
    ;; string[] _classes
    (apply #'+ (mapcar #'(lambda (x) (+ 4 (length x))) _classes)) 4
    ;; float32[] _distance
    (* 4    (length _distance)) 4
    ;; int64[] _x_center
    (* 8    (length _x_center)) 4
    ;; int64[] _y_center
    (* 8    (length _y_center)) 4
    ;; int16[] _id
    (* 2    (length _id)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string[] _classes
     (write-long (length _classes) s)
     (dolist (elem _classes)
       (write-long (length elem) s) (princ elem s)
       )
     ;; float32[] _distance
     (write-long (length _distance) s)
     (dotimes (i (length _distance))
       (sys::poke (elt _distance i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; int64[] _x_center
     (write-long (length _x_center) s)
     (dotimes (i (length _x_center))
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke (elt _x_center i) (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class (elt _x_center i)) (= (length ((elt _x_center i) . bv)) 2)) ;; bignum
              (write-long (ash (elt ((elt _x_center i) . bv) 0) 0) s)
              (write-long (ash (elt ((elt _x_center i) . bv) 1) -1) s))
             ((and (class (elt _x_center i)) (= (length ((elt _x_center i) . bv)) 1)) ;; big1
              (write-long (elt ((elt _x_center i) . bv) 0) s)
              (write-long (if (>= (elt _x_center i) 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long (elt _x_center i) s)(write-long (if (>= (elt _x_center i) 0) 0 #xffffffff) s)))
       )
     ;; int64[] _y_center
     (write-long (length _y_center) s)
     (dotimes (i (length _y_center))
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke (elt _y_center i) (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class (elt _y_center i)) (= (length ((elt _y_center i) . bv)) 2)) ;; bignum
              (write-long (ash (elt ((elt _y_center i) . bv) 0) 0) s)
              (write-long (ash (elt ((elt _y_center i) . bv) 1) -1) s))
             ((and (class (elt _y_center i)) (= (length ((elt _y_center i) . bv)) 1)) ;; big1
              (write-long (elt ((elt _y_center i) . bv) 0) s)
              (write-long (if (>= (elt _y_center i) 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long (elt _y_center i) s)(write-long (if (>= (elt _y_center i) 0) 0 #xffffffff) s)))
       )
     ;; int16[] _id
     (write-long (length _id) s)
     (dotimes (i (length _id))
       (write-word (elt _id i) s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string[] _classes
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _classes (make-list n))
     (dotimes (i n)
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setf (elt _classes i) (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
     ))
   ;; float32[] _distance
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _distance (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _distance i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;; int64[] _x_center
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _x_center (instantiate integer-vector n))
     (dotimes (i n)
#+(or :alpha :irix6 :x86_64)
      (setf (elt _x_center i) (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf (elt _x_center i) (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
     ))
   ;; int64[] _y_center
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _y_center (instantiate integer-vector n))
     (dotimes (i n)
#+(or :alpha :irix6 :x86_64)
      (setf (elt _y_center i) (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf (elt _y_center i) (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
     ))
   ;; int16[] _id
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _id (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _id i) (sys::peek buf ptr- :short)) (incf ptr- 2)
     ))
   ;;
   self)
  )

(setf (get display_test::Pub_class_distance :md5sum-) "26a7eb42f6a9f1a1625843bee8a7eb06")
(setf (get display_test::Pub_class_distance :datatype-) "display_test/Pub_class_distance")
(setf (get display_test::Pub_class_distance :definition-)
      "string[] classes
float32[] distance 
int64[] x_center
int64[] y_center
int16[] id
")



(provide :display_test/Pub_class_distance "26a7eb42f6a9f1a1625843bee8a7eb06")



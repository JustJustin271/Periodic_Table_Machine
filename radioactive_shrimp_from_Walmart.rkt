(define (radioactive x)
  (cond[(not(integer? x)) "Please try again with a valid input"]
       [(= x 43) "Radioactive! :)"]
       [(= x 61) "Radioactive! :)"]
       [(and(<= x 42)(>= x 1)) "Not Radioactive :D"]
       [(and(>= x 44) (<= x 82)) "Not Radioactive :D"]
       [(>= x 119) "Element not discovered yet :/"]
       [(>= x 83) "Radioactive! :)"]
       [else "Please input a valid atomic number D:"]))

;(check-expect (radioactive 6) "Not Radioactive :D")
        ;Carbon is not radioactive

;(check-expect (radioactive 92) "Radioactive :)")
        ;Uranium is radioactive

;--- Testing Area ---

(radioactive 5)
(radioactive 92)

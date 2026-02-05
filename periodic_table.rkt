(define (name? x) ;Names of the elements
  (cond [(not (integer? x)) "Please enter a whole number."] ;Elements from 1 - 18
        [(= x 1) "Hydrogen"]
        [(= x 2) "Helium"]
        [(= x 3) "Lithium"]
        [(= x 4) "Beryllium"]
        [(= x 5) "Boron"]
        [(= x 6) "Carbon"]
        [(= x 7) "Nitrogen"]
        [(= x 8) "Oxygen"]
        [(= x 9) "Fluorine"]
        [(= x 10) "Neon"]
        [(= x 11) "Sodium"]
        [(= x 12) "Magnesium"]
        [(= x 13) "Aluminium"]
        [(= x 14) "Silicon"]
        [(= x 15) "Phosphorus"]
        [(= x 16) "Sulfur"]
        [(= x 17) "Chlorine"]
        [(= x 18) "Argon :D"]
        [else "Error"]))

(define (group? x) ;Groups these elements belong in
  (cond [(not (integer? x)) "Please enter a whole number."]
        [(= x 1) "Gas"]
        [(= x 2) "Noble Gas"]
        [(= x 3) "Alkali Metal"]
        [(= x 4) "Alkaline Earth Metal"]
        [(= x 5) "Metalloid"]
        [(and (>= x 6) (<= x 9)) "Non-Metal"]
        [(= x 10) "Noble Gas"]
        [(= x 11) "Alkali Metal"]
        [(= x 12) "Alkaline Earth Metal"]
        [(= x 13) "Post-Transition Metal"]
        [(= x 14) "Metalloid"]
        [(and (>= x 15) (<= x 17)) "Non-Metal"]
        [(= x 18) "Noble Gas :D"]
        [else "Error"]))

(define (element-info x) ;Smashes both of the table together
  (if (equal? (name? x) "Error") ;If Error is produced from one of them, it will result in a proper error message
  "Element hasn't entered in database yet, please try again later :)"
  (string-append (name? x) " is a(n) " (group? x) "! :D"))) ;Utilizes String Append to form a proper ssentence, question makes are used for asking a question to the function with an input for the x - value


;Type your Atomic number (1-18) below! :D
(element-info 6)
;I haven't learned user inputs yet and probably not available on the school Chromebook :(

;Made using the Racket language, learning it in class :)
;Feburary 4th, 2026

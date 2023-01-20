```scheme
;; O(n) (n - количество пробельных символов)
(define (string-trim-left s)
  (define (for s)
    (if (and (not (null? s)) (char-whitespace? (car s)))
        (for (cdr s))
        s))
  
  (list->string (for (string->list s))))

;; O(n), но также есть константа, но в ассимптотике константу мы выбрасываем
(define (string-trim-right s)
  (define (for s)
    (if (and (not (null? s)) (char-whitespace? (car s)))
        (for (cdr s))
        s))
  
  (list->string (reverse (for (reverse (string->list s))))))

;; O(n)
(define (string-trim s)
  (string-trim-left (string-trim-right s)))

;; O(min(len(a), len(b)))
(define (string-prefix? a b)
  (define (for a b)
    (or (null? a) 
        (and (not (null? b))
            (and (equal? (car a) (car b))
                (for (cdr a) (cdr b))))))
  
  (for (string->list a) (string->list b)))

;; O(min(len(a), len(b)))
(define (string-suffix? a b)
  (define (for a b)
    (or (null? a) 
        (and (not (null? b))
            (and (equal? (car a) (car b))
                (for (cdr a) (cdr b))))))
  
  (for (reverse (string->list a)) (reverse (string->list b))))

(define (string-infix? a b)
  (and (> (string-length b) 0)
       (or (string-prefix? a b)
           (string-infix? a (substring b 1)))))

;;O(n)
(define (string-split str sep)
  (define (for result now str sep)
    (if (null? str)
        (append result (list (string now)))
        (if (string-prefix? (list->string sep) (list->string str))
            (for (append result (list (string now))) '()
              (string->list (substring (list->string str) (length sep))) sep)
            (for result (append now (car str)) (cdr str) sep))))

  (for '() '() (string->list str) (string->list sep)))
  ```

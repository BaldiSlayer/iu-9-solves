аволыфждовыфлд

```cpp

;; ~O((b - a) / d)
(define (my-range a b d)
  (if (< a b)
      (cons a (my-range (+ a d) b d))
      '()))

```

(define (my-flatten xs)
  (if (null? xs)
      '()
      (if (list? xs)
          (append (my-flatten (car xs)) (my-flatten (cdr xs)))
          (list xs))))

(define (my-flatten xs)
  (define (for result xs)
    ;; если дошли до конца списка, возвращаем ответ
    (if (null? xs)
        result
        (if (list? xs)
            (for (for result (car xs)) (cdr xs))
            (cons xs result))))
  
  (reverse (for '() xs)))



;; O(len(xs))
(define (my-element? x xs)
  (and (not (null? xs))
       (or (equal? (car xs) x)
           (my-element? x (cdr xs)))))                 

;; O(len(xs))
(define (my-filter pred? xs)
  (if (null? xs)
      '()
      (if (pred? (car xs))
          (append (list (car xs)) (my-filter pred? (cdr xs)))
          (my-filter pred? (cdr xs)))))

;; O(len(xs))
(define (my-fold-left op xs)
  (if (null? (cdr xs))
      (car xs)
      (my-fold-left op (append (list (op (car xs) (cadr xs))) (cddr xs)))))

;; O(len(xs))
(define (my-fold-right op xs)
  (define (my-fold-left-for-right op xs)
    (if (null? (cdr xs))
        (car xs)
        (my-fold-left-for-right op (append (list (op (cadr xs) (car xs))) (cddr xs)))))
  (my-fold-left-for-right op (reverse xs)))

# Домашняя работа №2

### Задание 1
```scheme
(define (my-range a b d)
  (if (< a b)
      (cons a (my-range (+ a d) b d))
      '()))

(define (my-flatten l)
  (if (null? l)
      '()
      (if (list? l)
          (append (my-flatten (car l)) (my-flatten (cdr l)))
          (list l))))
```

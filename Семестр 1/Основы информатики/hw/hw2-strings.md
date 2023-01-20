# Домашняя работа №2

### Задание 1

Определите следующие процедуры для обработки списков:

* Процедуру `(my-range a b d)`, возвращающую список чисел в интервале [a, b) с шагом d.
* Процедуру` my-flatten`, раскрывающую вложенные списки.
* Предикат `(my-element? x xs)`, проверяющий наличие элемента x в списке xs. Рекомендация: для проверки равенства элементов используйте встроенный предикат equal?.
* Предикат `(my-filter pred? xs)`, возвращающий список только тех элементов списка xs, которые удовлетворяют предикату pred?.
* Процедуру `(my-fold-left op xs)` для левоассоциативной свертки списка xs с помощью оператора (процедуры двух аргументов) op.
* Процедуру `(my-fold-right op xs)` для правоассоциативной свертки списка xs с помощью оператора (процедуры двух аргументов) op.

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

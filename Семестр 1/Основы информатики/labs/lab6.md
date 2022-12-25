### Вспомогательная структура данных — поток (stream)

```scheme
;; Конструктор потока
(define (make-stream items . eos)
  (if (null? eos)
      (make-stream items #f)
      (list items (car eos))))

;; Запрос текущего символа
(define (peek stream)
  (if (null? (car stream))
      (cadr stream)
      (caar stream)))

;; Запрос первых двух символов
(define (peek2 stream)
  (if (null? (car stream))
      (cadr stream)
      (if (null? (cdar stream))
          (list (caar stream))
          (list (caar stream) (cadar stream)))))

;; Продвижение вперёд
(define (next stream)
  (let ((n (peek stream)))
    (if (not (null? (car stream)))
        (set-car! stream (cdr (car stream))))
    n))

(define (expect stream term error)
    (if (equal? (peek stream) term)
        (next stream)
        (error #f)))    
```


## Задание 1

БНФ

```BNF
<frac>            ::= <signed-num> / <unsigned-num>
<signed-num>      ::= + <unsigned-num> | - <unsigned-num> | <unsigned-num>
<unsigned-num>    ::= ЦИФРА <num-tail>
<num-tail>        ::= ЦИФРА <num-tail> | <empty>
<empty>           ::=
```

```scheme

(define (check-frac str)
  (load "stream.scm") 

  (define (signed-num stream error)
    (cond ((equal? #\+ (peek stream))
           (next stream)
           (unsigned-num stream error))
          ((equal? #\- (peek stream))
           (next stream)
           (unsigned-num stream error))
          (else (unsigned-num stream error))))
  
  (define (unsigned-num stream error)
    (cond ((and (char? (peek stream))
                (char-numeric? (peek stream)))
           
           (next stream)
           (num-tail stream error))
          (else (error #f))))
  
  (define (frac stream error)
    (signed-num stream error)
    (expect stream #\/ error)
    (unsigned-num stream error))   
  
  (define (num-tail stream error)
    (cond ((and (char? (peek stream))
                (char-numeric? (peek stream)))
           (next stream)
           (num-tail stream error))
          (else #t)))
  
  (define stream (make-stream (string->list str) 'EOF))
  
  (call-with-current-continuation
   (lambda (error)
     (frac stream error)
     (eqv? (peek stream) 'EOF))))

(display (check-frac "1/2"))     ;;#t
(newline)
(display (check-frac "inf/2"))   ;;#f
(newline)
(display (check-frac "1/ui"))    ;;#f
(newline)
(display (check-frac "oi/dd"))   ;;#f
(newline)
(display (check-frac "12"))      ;;#f
(newline)
(display (check-frac ""))        ;;#f

```

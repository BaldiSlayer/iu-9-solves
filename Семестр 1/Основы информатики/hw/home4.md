;; TASK 1
(define memoized-factorial
  (let ((known-results '()))
    (lambda (n)
      (if (= n 0)
          1
          (if (assoc n known-results)
              result
              (let ((result (* (memoized-factorial (- n 1)) n)))
                (append '(n result) known-results)
                result))))))


;; TASK 2
;; Макрос будет предпочтительнее процедуры в данном случае из-за
;; порядка вычислений
(define-syntax lazy-cons
  (syntax-rules ()
    ((lazy-cons a b)
     (delay (cons a b)))))

(define (lazy-car p)
  (car (force p)))

(define (lazy-cdr p)
  (cdr (force p)))

(define (lazy-head xs k)
  (let loop ((xs xs)
             (k k)
             (result '()))
    (if (equal? k 0)
        (reverse result)
        (loop (lazy-cdr xs) (- k 1) (append (list (lazy-car xs)) result)))))

(define (lazy-ref xs k)
  (let loop ((xs xs)
             (k k))
    (if (equal? k 0)
        (lazy-car xs)
        (loop (lazy-cdr xs) (- k 1)))))

(define (naturals start)
  (lazy-cons start (naturals (+ 1 start))))

(define (lazy-factorial n)
  (define (range-factorials start val)
    (let loop ((new (+ start 1)))
      (lazy-cons val (range-factorials (+ 1 start) (* val (+ start 1))))))
  
  (lazy-ref (range-factorials 0 1) n))

;; TASK 3
(define (read-words)
  (let loop ((result '())
             (now '()))
    (let ((cur (read-char)))
      (if (eof-object? cur)
          (reverse result)
          (if (char-whitespace? cur)
              (if (null? now)
                  (loop result now)
                  (loop (append (list (list->string (reverse now))) result)
                        '()))
              (loop result (append (list cur) now)))))))

;; TASK 4

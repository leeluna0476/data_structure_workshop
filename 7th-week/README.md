# Subject
- Stack
  - Function Call Stack
  - Function Stack Frame

# Mission
- Implement a program that simulates the function below using a stack.
- 스택을 이용하여 아래 함수를 시뮬레이션하는 프로그램을 작성하기.
```python
def fib(N):
    if 0 <= N <= 1:
        return N
    else:
        return fib(N - 1) + fib(N - 2)
```
> **CAUTION 주의사항**
>
> No real recursion!
>
> 실제 재귀 호출을 하지 말 것.

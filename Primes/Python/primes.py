# 4.9 seconds with queue and 24 workers (which seems to be the sweet spot on a 6 core 12 threaded PC).

import multiprocessing
from multiprocessing import Manager
from typing import List
from datetime import datetime


# ---------------------------------------------------------------------------------------------------------------------


def is_prime(n: int) -> bool:
    """Checks to see if the passed number is a prime number."""

    i: int = 2
    while i < n:
        if n % i == 0:
            return False
        i += 1
    return True


# ---------------------------------------------------------------------------------------------------------------------


def calculate(start: int, stop: int, queue: multiprocessing.Queue) -> None:
    """Get prime numbers from start to stop"""

    i: int = start
    while i < stop:
        if is_prime(i):
            queue.put(i)
        i += 1


# ---------------------------------------------------------------------------------------------------------------------


def process() -> None:
    """Splits the task into multiple parts and manages worker threads."""

    with Manager() as manager:

        queue: multiprocessing.Queue = manager.Queue()
        tasks: List[multiprocessing.Process] = []
        total_workers: int = 24
        tasks_per_worker: int = 250001 // total_workers
        current_min: int = 2

        # Assign tasks.
        for _ in range(total_workers):
            tasks.append(
                multiprocessing.Process(
                    target=calculate,
                    args=(current_min, current_min + tasks_per_worker, queue),
                )
            )
            current_min += tasks_per_worker

        # Start and await tasks.
        for task in tasks:
            task.start()

        for task in tasks:
            task.join()

        total: List[int] = []

        while not queue.empty():
            total.append(queue.get())

        print(f"Found {len(total)} primes")


# ---------------------------------------------------------------------------------------------------------------------

if __name__ == "__main__":
    start: datetime = datetime.now()
    process()
    end: datetime = datetime.now()
    print(end-start)

# ---------------------------------------------------------------------------------------------------------------------

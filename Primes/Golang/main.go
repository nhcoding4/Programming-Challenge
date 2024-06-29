// 2.6 seconds with 24 workers on a 6 core 12 threaded PC.

package main

import (
	"fmt"
	"sync"
)

// --------------------------------------------------------------------------------------------------------------------

func main() {

	// Create channel, work pool and take the results.
	ch := make(chan int)
	pool := Pool{to_find: 250_001, workers: 24, ch: ch, waitgroup: sync.WaitGroup{}}
	go pool.Spin_Up()

	found_values := []int{}
	for {
		value, open := <-ch
		if !open {
			break
		}
		found_values = append(found_values, value)
	}

	fmt.Println("Found primes:", len(found_values))
}

// --------------------------------------------------------------------------------------------------------------------

func is_prime(n int) bool {
	// checks if a number is prime or not.
	for i := 2; i < n; i++ {
		if n%i == 0 {
			return false
		}
	}
	return true
}

// --------------------------------------------------------------------------------------------------------------------

type Pool struct {
	to_find   int
	workers   int
	ch        chan int
	waitgroup sync.WaitGroup
}

// --------------------------------------------------------------------------------------------------------------------

func (p *Pool) Process(start, stop int) {
	// Work that each thread is going to do.
	defer p.waitgroup.Done()

	for i := start; i < stop; i++ {
		if is_prime(i) {
			p.ch <- i
		}
	}
}

// --------------------------------------------------------------------------------------------------------------------

func (p *Pool) Spin_Up() {
	// Spins up X workers and assigns them tasks.
	current_min := 0
	tasks_per_worker := int(p.to_find / p.workers)
	p.waitgroup.Add(p.workers)

	for i := 0; i < p.workers; i++ {
		go p.Process(current_min, current_min+tasks_per_worker)
		current_min += tasks_per_worker
	}

	p.waitgroup.Wait()
	close(p.ch)

}

// --------------------------------------------------------------------------------------------------------------------

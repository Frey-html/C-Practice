# Calculate n prime numbers and print them
primeList = [2, 3]  # Initial prime numbers
n = int(input("Enter the number of prime numbers to be printed: "))

def calPrime(n):
    count = len(primeList)  # Start from the count of initial primes
    nextPrime = primeList[-1]  # Start searching from the last known prime

    while count < n:
        nextPrime += 2  # Only check odd numbers (since even numbers > 2 are not prime)
        isPrime = True
        for i in primeList:
            if i * i > nextPrime:
                break
            if nextPrime % i == 0:
                isPrime = False
                break
        if isPrime:
            primeList.append(nextPrime)
            count += 1

# If n <= 2, slice the list of already-known primes
if n <= len(primeList):
    print(primeList[:n])
else:
    calPrime(n)
    print(primeList)

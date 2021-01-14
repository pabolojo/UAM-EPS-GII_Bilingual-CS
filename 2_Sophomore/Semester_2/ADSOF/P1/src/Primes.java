import java.util.SortedSet;
import java.util.TreeSet;
/**
* This program check and print if each number is prime.
* It also prints all the prime numbers between 2 and the number passed as argument.
* If it is not prime, it will print its divisors.
*
*/
public class Primes {
    // we use an ordered set, implemented by TreeSet
    private SortedSet<Integer> primes= new TreeSet<>();
    private int max=1;

    /**
     * Gives the sorted set of primes
     *
     * @return cache with calculated primes
     */
    public SortedSet<Integer> getPrimes(){
        return primes;
    }

    /**
     * Returns a string with the data we want
     *
     * @return String with the sentence with te maximum and the prime numbers
     */
    public String toString(){
        return "Primes up to "+ max+ " = "+primes;
    }

    /**
    * Checks if the input is less than 2 or greater than our maximum to update the primes
    *
    * @param n value to check
    * @return boolean value
    */
    public boolean isPrime(int n){
	   if (n<2) return false;
	   if (n>max) updatePrimes(n);
	   return primes.contains(n);
	}

   /**
    * This method calls checkPrime and adds it, if it is prime, for all
    * numbers between max+1 and n. Updates max at the end.
    *
    * @param n value to check
    */
   private void updatePrimes(int n){
        if(n <= max){
            return;
        }
        for(int i = max + 1; i <= n; i++){
            if(checkPrime(i)){
                primes.add(i);
            }
        }
        max = n;
    }

    /**
    * Checks if n is prime, assuming that the set of primes is updated with
    * all previous ones
    *
    * @param n value to check
    * @return if n is prime
    */
    private boolean checkPrime(int n){

        for(int p: primes){
            if(n%p==0){
                return false;
            }
        }

        return true;
    }
    /**
    * Save the prime divisors of the input number in a set
    *
    * @param n The integer that we want to check its divisors
    * @return cache with calculated divisors
    */
    public SortedSet<Integer> primeDivisors(int n){
        SortedSet<Integer> divisors= new TreeSet<>();
        for(int i = 2; i < n/2 + 1; i++){
            if(n % i == 0){
              if(primes.contains(i)){
                divisors.add(i);
              }
            }
        }
        return divisors;
    }

    /**
    * Main program that checks if a number is prime and prints
    * the prime numbers until the maximum and its prime divisors if it is not prime
    *
    * @param args The command line arguments
    */
    public static void main(String[] args){
        if(args.length<1){
            System.out.println("You should write at least one number");
        }else{
            Primes p = new Primes();
            for (String s: args){ //we traverse the array
                try {
                    int n = Integer.parseInt(s); //convert to integer
                    if(p.isPrime(n)){
                        System.out.println(n + " is prime");
                    }
                    else{
                        System.out.println(n + " is NOT prime");
                        System.out.println("Prime divisors of " + n + ": " + p.primeDivisors(n));
                    }
                    System.out.println(p);
                } catch (NumberFormatException nfe) {
                    System.out.println("Input " + s + " is not an integer");
                }

            }
        }
    }
}


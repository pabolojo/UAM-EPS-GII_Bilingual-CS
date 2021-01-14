import java.util.SortedSet;
import java.util.TreeSet;

/**
 * This class keeps ordered a set of integer numbers
 */
public class Order {
    // we use an ordered set, implemented by TreeSet
    private SortedSet<Integer> numbers= new TreeSet<>();

    /**
     * Constructor, with the array of strings
     * @param strings to insert, after converting them to numbers
     */
    public Order(String ... params){
        for (String s: params){ 		//we traverse the array
            int n= Integer.parseInt(s); 	//convert to integer
            numbers.add(n); 			//add to set
        }
    }
    /**
     *
     * @return numbers
     */
    public SortedSet<Integer> getNumbers(){
        return numbers;
    }

    /**
     *
     * @return String representing this object
     */
    public String toString(){
        return "There are "+ numbers.size()+ " numbers"
                + ": " + numbers; //or +numbers.toString()
    }
    /**
     * Application entry point.
     *
     * This method orders the numbers of the command line     
     * @param args The arguments of the command line: should be at least two numbers
     */
    public static void main(String[] args) {
        if (args.length<2) {
            System.out.println("At least two numbers are expected");
            System.out.println("Returns the ordered set");
        }
        else {
            Order c = new Order(args);
            System.out.println(c); // We print the ordered set through the console
            // In java object destruction is automatic
        }
    }
}

package exercises_1_to_4.graph;

import java.util.*;
import java.util.function.Predicate;

import exercises_1_to_4.graph.Node;

/**
 * This is the Constrained Graph class.
 *
 */
public class ConstrainedGraph<A, B> extends Graph<A, B> {
	private Node<A> witness;
    /**
     * Constructor of this class.
     */
    public ConstrainedGraph() {
        super();
        this.witness = null;
    }

    /**
     * This method checks that all the nodes hold a condition
     *
     * @param p The predicate that is going to be tested
     * @return true or false
     */
    public boolean forAll(Predicate<Node<A>> p) {
        this.witness = null;
        boolean result = true;
        for (Node<A> n : this.nodes) {
            boolean test = p.test(n);
            result &= test;
            if (test) {
                this.witness = n;
            }
        }
        return result;
    }

    /**
     * This method checks that just one node hold a condition
     *
     * @param p The predicate that is going to be tested
     * @return true or false
     */
    public boolean one(Predicate<Node<A>> p) {
        int result = 0;
        Node<A> one = null;
        for (Node<A> n : this.nodes) {
            if (p.test(n)) {
                one = n;
                result++;
            }
            if (result == 2) {
                return false;
            }
        }
        if (result == 1) {
            this.witness = one;
        } else {
            this.witness = null;
        }
        return result == 1 ? true : false;
    }

    /**
     * This method checks that at least one node holds a condition
     *
     * @param p The predicate that is going to be tested
     * @return true or false
     */
    public boolean exists(Predicate<Node<A>> p) {
        this.witness = null;
        for (Node<A> n : this.nodes) {
            if (p.test(n)) {
                this.witness = n;
                return true;
            }
        }
        return false;
    }

    /**
     * This function returns an optional with the witness node
     * 
     * @return an optional with the witness if it exits, otherwise it will contain null
     */
    public Optional<Node<A>> getWitness() {
        return Optional.ofNullable(this.witness);
    }
}

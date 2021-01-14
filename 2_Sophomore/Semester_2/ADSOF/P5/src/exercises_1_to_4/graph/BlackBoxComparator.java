package  exercises_1_to_4.graph;

import java.util.*;
import java.util.function.Predicate;

/**
 * This is the BlackBox Comparator class.
 *
 */
public class BlackBoxComparator<A, B> implements Comparator<ConstrainedGraph<A, B>> {
    private Map<Criteria, List<Predicate<Node<A>>>> criterias = null;
    
    /**
     * Constructor of this class.
     */
    public BlackBoxComparator() {
        this.criterias = new EnumMap<Criteria, List<Predicate<Node<A>>>>(Criteria.class);
    }

    /**
     * Enumeration for the BlackBoxComparator.
     * It is an internal enum.
     */
    public enum Criteria {
        EXISTENTIAL {
        	/**
             * It will test the predicate passed by argument into the graph.
             * The return parameter is going to be true when there exists at least one node that
             * returns true on the test.
             * 
             * @param <A> Information of the node
             * @param <B> Information of the edge
             * @param p the predicate we are testing
             * @param graph the graph
             * @return true or false
             */
            @Override
            public <A, B> boolean test(Predicate<Node<A>> p, ConstrainedGraph<A, B> graph) {
                return graph.exists(p);
            }
        },
        UNITARY {
        	/**
             * It will test the predicate passed by argument into the graph.
             * The return parameter is going to be true when there is just one node that holds the condition
             * 
             * @param <A> Information of the node
             * @param <B> Information of the edge
             * @param p the predicate we are testing
             * @param graph the graph
             * @return true or false
             */
            @Override
            public <A, B> boolean test(Predicate<Node<A>> p, ConstrainedGraph<A, B> graph) {
                return graph.one(p);
            }
        },
        UNIVERSAL {
        	/**
             * It will test the predicate passed by argument into the graph.
             * The return parameter is going to be true when all the nodes holds the condition
             * 
             * @param <A> Information of the node
             * @param <B> Information of the edge
             * @param p the predicate we are testing
             * @param graph the graph
             * @return true or false
             */
            @Override
            public <A, B> boolean test(Predicate<Node<A>> p, ConstrainedGraph<A, B> graph) {
                return graph.forAll(p);
            }
        };

        /**
         * Abstract function that will be configured depending on the type of the criteria.
         * It will test the predicate passed by argument into the graph.
         * 
         * @param <A> Information of the node
         * @param <B> Information of the edge
         * @param p the predicate we are testing
         * @param graph the graph
         * @return true or false
         */
        public abstract <A, B> boolean test(Predicate<Node<A>> p, ConstrainedGraph<A, B> graph);
    }

    /**
     * This method adds the criteria
     * @param c The criteria to add
     * @param p The predicate of nodes
     * @return The criteria.
     */
    public BlackBoxComparator<A, B> addCriteria(Criteria c, Predicate<Node<A>> p) {
        if (!this.criterias.containsKey(c)) {
            criterias.put(c, new ArrayList<Predicate<Node<A>>>());
        }
        this.criterias.get(c).add(p);
        return this;
    }

    /**
     * This method compares the graphs
     * @param cGraph1 The first graph
     * @param cGraph2 The second graph
     * @return The difference between the first and second graphs.
     */
    @Override
    public int compare(ConstrainedGraph<A, B> cGraph1, ConstrainedGraph<A, B> cGraph2) {
        int pointsG1 = 0;
        int pointsG2 = 0;

        for (Criteria c : this.criterias.keySet()) {
            for (Predicate<Node<A>> p : this.criterias.get(c)) {
                if (c.test(p, cGraph1)) {
                    pointsG1++;
                }
                if (c.test(p, cGraph2)) {
                    pointsG2++;
                }
            }
        }

        return pointsG1 - pointsG2;
    }
}

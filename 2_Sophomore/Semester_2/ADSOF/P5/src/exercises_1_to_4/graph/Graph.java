package  exercises_1_to_4.graph;

import java.util.*;

import exercises_1_to_4.graph.Edge;
import exercises_1_to_4.graph.Node;

/**
 * These are the functions and variables that define the Graph objects, the
 * Graph class.
 *
 */
public class Graph<A, B> implements Collection<Node<A>> {

    protected Set<Node<A>> nodes;
    private int numberNodes = 0;

    /**
     * Constructor of this class.
     */
    public Graph() {
        this.nodes = new LinkedHashSet<Node<A>>();
    }

    /**
     * Method that outputs the size of the graph.
     * 
     * @return size
     */
    @Override
    public int size() {
        return this.nodes.size();
    }

    /**
     * Method that tells us if the graph is empty or not.
     * 
     * @return boolean
     */
    @Override
    public boolean isEmpty() {
        return this.nodes.isEmpty();
    }

    /**
     * Method that tells us if the graph contains said object.
     * 
     * @param o The object to be searched
     * @return true or false
     */
    @Override
    public boolean contains(Object o) {
        if (o == null) {
            return false;
        }
        return this.nodes.contains(o);
    }

    /**
     * Method that iterates the nodes.
     * @return the iteration
     */
    @Override
    public Iterator<Node<A>> iterator() {
        return this.nodes.iterator();
    }

    /**
     * It returns an array of objects with the nodes in the graph
     *
     * @return the nodes array
     */
    @Override
    public Object[] toArray() {
        return this.nodes.toArray();
    }

    /**
     * Returns an array containing all of the elements in the nodes set
     * 
     * @return the array of nodes
     */
    @Override
    public <C> C[] toArray(C[] a) {
        return this.nodes.toArray(a);
    }

    /**
     * Method that adds a node to the graph.
     * 
     * @param n The node to be introduced
     * @return T or F
     */
    @Override
    public boolean add(Node<A> n) {
        if (this.nodes.add(n)) {
            n.setId(this.numberNodes);
            this.numberNodes++;
            return true;
        }
        return false;
    }

    /**
     * Method that removes an object from the graph.
     * 
     * @param o The object to be removed
     * @return T or F or the result of removing the object
     */
    @Override
    public boolean remove(Object o) {
        if (o == null) {
            return false;
        }
        if (!(o instanceof Node<?>)) {
            return false;
        }
        Node<?> n = (Node<?>) o;
        for (Node<A> node : nodes) {
            node.removeEdges(n);
        }
        return this.nodes.remove(o);
    }

    /**
     * Method that checks if a collection of objects are in the collection.
     * 
     * @param c Collection of objects that are to be found
     * @return true or false
     */
    @Override
    public boolean containsAll(Collection<?> c) {
        return this.nodes.containsAll(c);
    }

    /**
     * Method that adds a number of nodes to the graph.
     * 
     * @param c The nodes to be introduced
     * @return T or F
     */
    @Override
    public boolean addAll(Collection<? extends Node<A>> c) {
        for (Node<A> n : c) {
            if (!this.add(n)) {
                return false;
            }
        }
        return true;
    }

    /**
     * Method that removes objects from the graph.
     * 
     * @param c The objects to be removed
     * @return T or F or the result of removing the edges
     */
    @Override
    public boolean removeAll(Collection<?> c) {

        for (Object o : c) {
            if (o == null) {
                return false;
            }
            if (!(o instanceof Node<?>)) {
                return false;
            }
            Node<?> n = (Node<?>) o;
            for (Node<A> node : nodes) {
                node.removeEdges(n);
            }
        }

        return this.nodes.removeAll(c);
    }

    /**
     * Method that retains nodes from the graph.
     * 
     * @param c The collection of nodes to be check for retain
     * @return The nodes have been retrained
     */
    @Override
    public boolean retainAll(Collection<?> c) {
        return this.nodes.retainAll(c);
    }

    /**
     * Method that clears nodes from the graph.
     */
    @Override
    public void clear() {
        this.nodes.clear();
    }

    /**
     * This method connects two nodes with an edge that contains the information
     * info.
     * 
     * @param n1   the from node
     * @param info information that the edge will contain
     * @param n2   the destination node
     */
    public void connect(Node<A> n1, B info, Node<A> n2) {
        if (!this.nodes.contains(n1) || !this.nodes.contains(n2)) {
            return;
        }
        Edge<A, B> e = new Edge<A, B>(n1, info, n2);
        n1.addEdge(e);
    }

    /**
     * This method outputs a string with information about the graph.
     * 
     * @return String containing all the information of the object.
     */
    @Override
    public String toString() {
        String s = "Nodes:\n";

        for (Node<A> n : this.nodes) {
            s = s.concat(n + "\n");
        }
        s = s.concat("Edges:\n");
        for (Node<A> n : this.nodes) {
            List<Edge<A, ?>> edges = n.getEdges();
            for (Edge<A, ?> e : edges) {
                s = s.concat(e + "\n");
            }
        }

        return s;
    }

}

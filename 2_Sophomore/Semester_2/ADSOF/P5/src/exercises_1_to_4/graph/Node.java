package exercises_1_to_4.graph;
import java.util.*;

/**
 * These are the functions and variables that define the Node objects, the Node
 * class.
 *
 */
public class Node<A> {
    private A info;
    private List<Edge<A, ?>> edges;
    private int number;

    /**
     * Constructor of this class.
     * 
     * @param info information of the node
     */
    public Node(A info) {
        this.info = info;
        this.edges = new ArrayList<Edge<A, ?>>();
    }

    /**
     * This method outputs a string with information about the node.
     * 
     * @return String containing all the information of the object.
     */
    @Override
    public String toString() {
        return this.number + " [" + this.info + "]";
    }

    /**
     * This method tells if a node is connected with other one by its information.
     * 
     * @param info2 information of the second node
     * @return boolean
     */
    public boolean isConnectedTo(A info2) {
        for (Edge<A, ?> e : edges) {
            if (e.getToNode().getValue().equals(info2)) {
                return true;
            }
        }
        return false;
    }

    /**
     * This method tells if a node is connected with other one.
     * 
     * @param neighbour the second node
     * @return boolean
     */
    public boolean isConnectedTo(Node<A> neighbour) {
        for (Edge<A, ?> e : edges) {
            if (e.getToNode().equals(neighbour)) {
                return true;
            }
        }
        return false;
    }

    /**
     * This method overrides the default equal method among Nodes.
     * 
     * @param o. The object to be compared
     * @return true if both Nodes are equal. False otherwise
     */
    @Override
    public boolean equals(Object o) {
        if (o == null) {
            return false;
        }
        if (!(o instanceof Node<?>)) {
            return false;
        }
        Node<?> n = (Node<?>) o;

        if (n == this) {
            return true;
        }

        if (n.number == this.number) {
            return true;
        }
        return false;
    }

    /**
     * It generates a hashCode for the Node
     * 
     * @return int the hash code generated
     */
    @Override
    public int hashCode() {
        return this.info.hashCode();
    }

    /**
     * It adds an edge to the edge list.
     * 
     * @param e edge that we want to add.
     */
    public void addEdge(Edge<A, ?> e) {
        edges.add(e);
    }

    /**
     * This function returns a collection with the nodes that are connected with
     * 'this'.
     * 
     * @return neighbours a set with the neighbour nodes.
     */
    public Collection<Node<A>> neighbours() {
        Collection<Node<A>> neighbours = new LinkedHashSet<Node<A>>();

        for (Edge<A, ?> e : edges) {
            neighbours.add(e.getToNode());
        }

        return neighbours;
    }

    /**
     * Number getter.
     * 
     * @return number
     */
    public int getNumber() {
        return this.number;
    }

    /**
     * Information getter.
     * 
     * @return info
     */
    public A getValue() {
        return this.info;
    }

    /**
     * Information setter.
     * 
     * @param info that will be set to the node
     */
    public void setValue(A info) {
        this.info = info;
    }

    /**
     * It removes all the edges that goes from this to the node passed as argument.
     * 
     * @param n node that will be checked.
     */
    public void removeEdges(Node<?> n) {
        for (Edge<A, ?> e : edges) {
            if (e.getToNode().equals(n)) {
                edges.remove(e);
            }
        }
    }

    /**
     * Function that returns a set with the values of the edges that goes from this
     * to n2.
     * 
     * @param n2 that we want to check.
     * @return edgeValues a set with the values of the edges.
     */
    public List<? extends Object> getEdgeValues(Node<A> n2) {
        List<? super Object> edgeValues = new LinkedList<>();

        for (Edge<A, ?> e : edges) {
            if (e.getToNode().equals(n2)) {
                edgeValues.add(e.getEdgeValue());
            }
        }
        return edgeValues;
    }

    /**
     * Edges getter.
     * 
     * @return edges the list of edges of the node.
     */
    public List<Edge<A, ?>> getEdges() {
        return this.edges;
    }

    /*
     * Id setter.
     * 
     * @param id int number that represents the id of the node in the graph
     **/
    public void setId(int id) {
        this.number = id;
    }
}

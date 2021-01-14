package  exercises_1_to_4.graph;
/**
 * These are the functions and variables that define the Edge objects, the Edge class.
 *
 */
public class Edge<A, B> {
    private Node<A> from;
    private Node<A> to;
    private B info;

    /**
     * Constructor of this class.
     * 
     * @param from Node, where the edge starts
     * @param info information of the edge
     * @param to Node, where the edge ends
     */
    public Edge(Node<A> from, B info, Node<A> to) {
        this.from = from;
        this.to = to;
        this.info = info;
    }
    
    /**
     * Information getter
     * 
     * @return info the edge value
     */
    public B getEdgeValue() {
        return this.info;
    }
    
    /**
     * Destination node getter
     * 
     * @return to destination Nde
     */
    public Node<A> getToNode() {
        return this.to;
    }
    
    /**
     * This method outputs a string with information about the edge.
     * 
     * @return String containing all the information of the object.
     */
    @Override
    public String toString() {
        return "( " + from.getNumber() + " --" + this.info.toString() + "--> " + to.getNumber() + " )";
    }
}

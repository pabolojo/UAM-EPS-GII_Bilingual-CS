package exercise_5.rules;

import java.util.*;
/**
 * This is the Triggered Rule class.
 *
 */
public class TriggeredRule<A extends Observable> extends Rule<A> implements Observer {

    private A item;

    /**
     * Constructor of this class.
     * It is private so we can control its creation
     * 
     * @param name The name of the rule
     * @param description The description of the rule
     */
    private TriggeredRule(String name, String description) {
        super(name, description);
    }

    /**
     * Triggered rule creator
     * @param rule string that will contain the name
     * @return the new triggered rule created
     */
    public static <A extends Observable> TriggeredRule<A> trigRule(String rule) {
        return new TriggeredRule<A>(rule, null);
    }

    /**
     * This method sets the triggered rule properties.
     * 
     * @param item The item which will be Triggered
     * @param name The name of the trigger
     * @return The triggered rule
     */
    public TriggeredRule<A> trigger(A item, String name) {
        item.addObserver(this);
        this.item = item;
        this.description = name;
        return this;
    }

    /**
     * This method updates an object.
     * 
     * @param o the observable object
     * @param arg the object indicating what has changed
     */
    @Override
    public void update(Observable o, Object arg) {
        if (o == null || arg == null || !(o.equals(this.item)) || !(arg.equals(this.description))) {
            return;
        }
        if (this.test(item)) {
            this.perform(item);
        }
    }

}


package exercises_1_to_4.rules;

import java.util.function.*;

/**
 * This is the Rule class.
 *
 */

public class Rule<T> {
	private String name;
    private String description;
    private Predicate<T> condition;
    private Consumer<T> perform;

    /**
     * Constructor of this class.
     * It is private so we can control its creation.
     * 
     * @param name The rule name
     * @param description The rule description
     */
    public Rule(String name, String description) {
        this.name = name;
        this.description = description;
    }

    /**
     * Static method to create a rule.
     * 
     * @param name The rule name
     * @param description The rule description
     * @return the rule that we have created
     */
    public static <T> Rule<T> rule(String name, String description) {
        return new Rule<T>(name, description);
    }

    /**
     * Condition predicate setter.
     * 
     * @param condition
     * @return the rule
     */
    public Rule<T> when(Predicate<T> condition) {
        this.condition = condition;
        return this;
    }

    /**
     * Consumer function setter.
     * 
     * @param perform
     * @return the rule
     */
    public Rule<T> exec(Consumer<T> perform) {
        this.perform = perform;
        return this;
    }

    /**
     * This method will test the condition of the rule on an object
     * 
     * @param object where we want to test the function
     * @return boolean
     */
    public boolean test(T object) {
        return this.condition.test(object);
    }
    
    /**
     * This method will accept the consumer function of the rule on an object
     * 
     * @param object where we want to apply the function
     */
    public void perform(T object) {
        this.perform.accept(object);
    }
    
    /**
     * The hash code generator method.
     * 
     * @return the hash code of  rule
     */
    @Override
    public int hashCode() {
        return this.name.hashCode();
    }

    /**
     * This method checks if a rule is equals to other rule.
     * 
     * @return boolean
     */
    @Override
    public boolean equals(Object o) {
        if (o == null) {
            return false;
        }
        if (!(o instanceof Rule<?>)) {
            return false;
        }

        Rule<?> r = (Rule<?>) o;
        if (this.name.equals(r.name)) {
            return true;
        }
        return false;

    }

    /**
     * Description of the rule setter.
     * 
     * @param description 
     */
    public void setDescription(String description) {
        this.description = description;
    }
}

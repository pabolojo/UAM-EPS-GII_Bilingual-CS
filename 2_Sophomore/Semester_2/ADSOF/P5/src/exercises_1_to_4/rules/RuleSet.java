package exercises_1_to_4.rules;

import java.util.*;

import exercises_1_to_4.rules.Rule;

/**
 * This is the Rule Set class.
 *
 */
public class RuleSet<A> {
	protected Set<Rule<A>> rules;
    protected Collection<A> context;

    /**
     * Constructor of this class.
     */
    public RuleSet() {
        this.rules = new LinkedHashSet<Rule<A>>();
    }

    /**
     * This method adds a rule to the ruleset.
     * 
     * @return The rule has been added
     */
    public RuleSet<A> add(Rule<A> r) {
        this.rules.add(r);
        return this;
    }

    /**
     * Setter for context.
     * 
     * @param c the collection that is going to be setted as the context
     */
    public void setExecContext(Collection<A> c) {
        this.context = c;
    }

    /**
     * It will test a rule condition on the context and will apply it if test returns true
     */
    public void process() {
        for (A c : context) {
            for (Rule<A> r : rules) {
                if (r.test(c)) {
                    r.perform(c);
                }
            }
        }
    }
}

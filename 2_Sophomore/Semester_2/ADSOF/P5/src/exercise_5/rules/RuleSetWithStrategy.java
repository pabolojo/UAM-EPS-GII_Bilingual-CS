package exercise_5.rules;

import java.util.*;
import java.util.function.Predicate;

import exercise_5.rules.strategies.IStrategy;

/**
 * This is the Rule Set with strategy class.
 *
 */
public class RuleSetWithStrategy<A> extends RuleSet<A> implements Predicate<A> {

    private IStrategy<A> strategy;
    private Rule<A> rule;
    private A item;

    /**
     * Constructor of this class.
     * 
     *@param strategy The strategy to be used
     */
    public RuleSetWithStrategy(IStrategy<A> strategy) {
        super();
        this.strategy = strategy;

    }

    /**
     * This method adds a rule to the rule set.
     * 
     * @return The object RuleSetWithStrategy
     */
    public RuleSetWithStrategy<A> add(Rule<A> r) {
        super.add(r);
        return this;
    }

    /**
     * This method will call to the process method in strategy, so it can be performed.
     */
    @Override
    public void process() {
        this.strategy.process(this);
    }

    /**
     * Context collection getter.
     * 
     * @return context The context collection
     */
    public Collection<A> getContext() {
        return this.context;
    }

    /**
     * Rules collection getter.
     * 
     * @return rules The collection of rules
     */
    public Set<Rule<A>> getRules() {
        return this.rules;
    }

    /**
     * This method tests the rules on a object
     * 
     * @param t An object where we test the rule
     * @return Boolean
     */
    @Override
    public boolean test(A t) {
        for (Rule<A> r : this.rules) {
            if (r.test(t)) {
                this.rule = r;
                this.item = t;
                return true;
            }
        }
        return false;
    }

    /**
     * This method performs the action of the rule on the item
     */
    public void perform() {
        this.rule.perform(this.item);
    }
}

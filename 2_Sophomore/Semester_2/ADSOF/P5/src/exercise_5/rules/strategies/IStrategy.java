package exercise_5.rules.strategies;

import exercise_5.rules.RuleSetWithStrategy;
/**
 * This is the IStrategy interface.
 *
 */

public interface IStrategy<A> {
    /**
     * Method that needs to be overriden
     * It will apply the functions in the rules of the set into its context.
     * 
     * @param ruleSet the set of rules
     */
    public void process(RuleSetWithStrategy<A> ruleSet);
}

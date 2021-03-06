package  exercises_1_to_4.rules.strategies;

import exercises_1_to_4.rules.*;
/**
 * This is the As Long as Possible class.
 *
 */
public class AsLongAsPossible<A> implements IStrategy<A> {
	/**
	 * This method will apply the functions of the rules into the context as long as possible.
	 *
	 * @param ruleSet the set of rules
	 */
	@Override
    public void process(RuleSetWithStrategy<A> ruleSet) {
        while (ruleSet.getContext().stream().anyMatch(ruleSet)) {
            ruleSet.perform();
        }
    }
}

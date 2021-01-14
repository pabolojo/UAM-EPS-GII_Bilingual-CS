package exercises_1_to_4.rules.strategies;

import exercises_1_to_4.rules.*;
/**
 * This is the Sequence class.
 *
 */
public class Sequence<A> implements IStrategy<A> {

	/**
	 * This method will apply the functions of the rules into the context in sequence.
	 *
	 * @param ruleSet the set of rules
	 */
	@Override
    public void process(RuleSetWithStrategy<A> ruleSet) {
        for (A c : ruleSet.getContext()) {
            for (Rule<A> r : ruleSet.getRules()) {
                if (r.test(c)) {
                    r.perform(c);
                    break;
                }
            }
        }
    }
}

package sections_1_to_5.metricSystems;

import sections_1_to_5.magnitude.*;
import sections_1_to_5.magnitude.exceptions.*;
import sections_1_to_5.metricSystems.MetricSystemConverter;
import sections_1_to_5.units.IPhysicalUnit;

/**
 * These are the functions and variables that define the MetricSystemConverter
 * class. It implements the interface IMetricSystemConverter.
 * 
 */
public abstract class MetricSystemConverter implements IMetricSystemConverter {

	IMetricSystem sourceSystem;
	IMetricSystem targetSystem;
	protected double value;

	/**
	 * Constructor of this class.
	 * 
	 * @param sourceSystem Source metric system
	 * @param targetSystem Target metric system
	 * @param value Value of the conversion from the base unit of one system to the base unit of the other one
	 */
	public MetricSystemConverter(IMetricSystem sourceSystem, IMetricSystem targetSystem, double value) {
		this.sourceSystem = sourceSystem;
		this.targetSystem = targetSystem;
		this.value = value;
	}

	/**
	 * sourceSystem getter.
	 * @return sourceSystem
	 */
	@Override
	public IMetricSystem sourceSystem() {
		return sourceSystem;
	}

	/**
	 * targetSystem getter.
	 * @return targetSystem
	 */
	@Override
	public IMetricSystem targetSystem() {
		return targetSystem;
	}

	/**
	 * Function that modifies the actual converter to return a converter that goes from the target to source.
	 * @return reverse IMetricSystemConverter
	 */
	@Override
	public IMetricSystemConverter reverse() {
		IMetricSystem aux = this.sourceSystem;
		this.sourceSystem = this.targetSystem;
		this.targetSystem = aux;
		this.value = 1 / this.value;
		return this;
	}

	/**
	 * Method that transforms a Magnitude into a magnitude of a different system.
	 * @param from IMagnitude that we want to transform.
	 * @param to IPhysicalUnit in which we want our Magnitude to be at the end.
	 * @return mag IMagnitude.
	 * @throws UnknownUnitException if the metric systems do not have a converter or there is a Quantity Exception.
	 */
	@Override
	public IMagnitude transformTo(IMagnitude from, IPhysicalUnit to) throws UnknownUnitException {
		Magnitude mag;

		if (from.getUnit().getMetricSystem().base().equals(this.targetSystem.base())
				&& to.getMetricSystem().base().equals(this.sourceSystem.base())) {

			this.reverse();
		}

		if (!(from.getUnit().getMetricSystem().base().equals(this.sourceSystem.base())
				&& to.getMetricSystem().base().equals(this.targetSystem.base()))) {

			throw new UnknownUnitException(from.getUnit(), to);
		}

		try {
			from.transformTo(from.getUnit().getMetricSystem().base());
		} catch (QuantityException e) {
			throw new UnknownUnitException(from.getUnit(), to);
		}
		
		mag = (Magnitude) from;
		mag.setValue(from.getValue() * this.value);
		mag.setUnit(to.getMetricSystem().base());

		try {
			mag.transformTo(to);
		} catch (QuantityException e) {
			throw new UnknownUnitException(mag.getUnit(), to);
		}
		return mag;

	}
}


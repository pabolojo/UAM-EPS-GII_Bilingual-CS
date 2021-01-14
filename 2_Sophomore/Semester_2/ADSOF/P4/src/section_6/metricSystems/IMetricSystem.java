package section_6.metricSystems;

import java.util.Collection;

import section_6.units.physicalUnit.IPhysicalUnit;

/**
 * These are the functions and variables that define the MetricSystem interface.
 *
 */
public interface IMetricSystem {

    /**
     * Method that returns the base physical unit.
     * 
     * @return IPhysicalUnit
     */
    IPhysicalUnit base();

    /**
     * Method that returns a collection with all the units.
     * 
     * @return Collection
     */
    Collection<IPhysicalUnit> units();
}

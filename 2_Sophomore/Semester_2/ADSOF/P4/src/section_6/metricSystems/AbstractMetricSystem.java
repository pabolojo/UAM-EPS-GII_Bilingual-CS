package section_6.metricSystems;

import java.util.*;

import section_6.units.physicalUnit.IPhysicalUnit;

/**
 * These are the functions and variables that define the MetricSystem class. It
 * implements the interface IMetricSystem.
 * 
 */
public abstract class AbstractMetricSystem implements IMetricSystem {

    private IPhysicalUnit base;

    private List<IPhysicalUnit> units;

    protected static IMetricSystemConverter converter = null;

    /**
     * Constructor of this class.
     */
    public AbstractMetricSystem() {
        this.base = null;
        units = new ArrayList<IPhysicalUnit>();
    }

    /**
     * Base unit of a metric system setter.
     * 
     * @param base
     */
    protected void setBaseUnit(IPhysicalUnit base) {
        this.base = base;
    }

    /**
     * Method that adds a Physical Unit into the collection of units.
     * 
     * @param unit
     */
    protected void addPhysicalUnit(IPhysicalUnit unit) {
        units.add(unit);
    }

    /**
     * Method that returns the base physical unit.
     * 
     * @return base
     */
    @Override
    public IPhysicalUnit base() {
        return this.base;
    }

    /**
     * Method that returns a collection with all the units.
     * 
     * @return units an array list.
     */
    @Override
    public Collection<IPhysicalUnit> units() {
        return this.units;
    }

    /**
     * Method that returns the converter of a Metric System.
     * 
     * @return converter.
     */
    public static IMetricSystemConverter getConverter() {
        return AbstractMetricSystem.converter;
    }
}

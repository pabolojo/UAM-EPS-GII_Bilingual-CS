package ads.p2.billing;
/**
* These are the functions and variables that define the Book objects, the Book class.
*
*/
public class Book extends Article {
  private String category;

    /**
     * Constructor of this class
     *
     * @param id identifier.
     * @param desc description.
     * @param price The units price.
     * @param categ Category.
     */
  public Book(long id, String desc, double price, String categ) {
        super(id, desc, price);
        category = categ;
    }

    /**
    * Category getter.
    * @return category.
    */
    public String getCategory() { return category; }
    /**
    * Category setter.
    * @param categ The category we are going to set.
    */
    public void setCategory(String categ) { category = categ; }
    /**
    * Defines the public VAT.
    * @return The calculated VAT.
    */
    public double typeVAT() { return 0.04; }
    /**
    * Calculates the corresponding discount.
    * @param units The amount of books of the same kind that will recieve the discount.
    * @return The units price with discount in the "textbook" case, in the "Collection" case or in case of anything else, 0
    */
    public double discount(double units) {
        if (category.equals("Textbook")) return getUnitPrice() * 0.15 * units;
    else if (category.equals("Collection") && units > 2) return getUnitPrice() * 0.5 * (units - 2);
        else return 0.0;
    }
}

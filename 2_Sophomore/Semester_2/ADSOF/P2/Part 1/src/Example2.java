package ads.p2;

import ads.p2.billing.*;
/**
* This program first creates three new books, the first two being of type Article and the third one of type book,
* and a Tobacco object.
* Then it prints one by one the amount of objects and the final prize of each quantity.
*
*/

public class Example2 {
	/**
    * Main program 
    *
    * @param args The command line arguments
    */
	public static void main(String args[]) {
		Article a3 = new Book(940111, "UML", 15, "Textbook");
		Article a4 = new Book(940607, "Classic readings", 10, "Collection");
		Book a5 = new Book(940607, "Fifty fifty", 3.25, "Unclassified");
		Tobacco a6 = new Tobacco(690023, "Marlboro", 1.75);

		int cant = 2;
		System.out.println(cant + " units of " + a3 + " Final price: " + a3.totalPrice(cant));
		cant = 5;
		System.out.println(cant + " units of " + a4 + " Final price: " + a4.totalPrice(cant));
		cant = 4;
		System.out.println(cant + " units of " + a5 + " Final price: " + a5.totalPrice(cant));
		cant = 1;
		System.out.println(cant + " units of " + a6 + " Final price: " + a6.totalPrice(cant));
	}
}

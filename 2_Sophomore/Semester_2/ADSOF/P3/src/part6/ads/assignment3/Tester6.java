package part6.ads.assignment3;;
/**
 * This is the class for the Tester 6, the optional part. It test the functions created in
 * the Stock Management class and the ones modified in other classes.
 */
public class Tester6 {

	public static void main(String[] args) {
		StockManagement s = StockManagement.getStockManagement();
		Appliance tv1 = new Television("Loewe", "Art 48 4K Plata", 1699.00,
				EnergyEfficiency.A, 48);
		Appliance tv2 = new Television("LG", "32LF592U", 271.92,
				EnergyEfficiency.C, 32);
		Appliance wash1 = new Washer("Indesit", "XWE 91483 X", 329.0,
				EnergyEfficiency.A, new Dimension(59.5, 60.5, 85.0), 72, 9.5, 1500);
		Appliance frigo1 = new Refrigerator("Bosch", "KGN39VW21", 599.0,
				EnergyEfficiency.A, new Dimension(60, 65, 201), 83.0, true);
		
		/*Add units to the inventory*/
		s.updateProduct(tv1, 10);
		s.updateProduct(tv2, 20);
		s.updateProduct(wash1, 5);
		s.updateProduct(frigo1, 15);
		
		System.out.println("This is the inventory: \n");
		/*Prints the whole inventory*/
		System.out.println(s.getInventory());
		
		/*Create some sales*/
		Sale[] sales = new Sale[5];
	    sales[0] = new Sale(tv2);
	    sales[1] = new HomeDeliverySale(tv1);
	    sales[2] = new CannarySale(wash1); 
	    sales[3] = new HomeDeliverySale(wash1, frigo1);
	    sales[4] = new CannarySale(tv1);
	    
	    System.out.println("This is the updated inventory: \n");
	    
	    /*Prints the inventory, and checks if the units have been updated*/
	    System.out.println(s.getInventory());
	    
	    System.out.println("This is the inventory of the Televisions type: \n");
	    
	    /*Prints the Television inventory*/
	    System.out.println(s.getInventory("Television"));
	    
	    /*Removes a product*/
	    s.removeProduct(tv1);
	    
	    System.out.println("This is the updated inventory of the Televisions type: \n");
	    
	    /*Prints the Television inventory again and checks if the product has been deleted*/
	    System.out.println(s.getInventory("Television"));
	}

}


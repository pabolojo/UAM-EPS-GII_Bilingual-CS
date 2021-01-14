package ads.assignment3;

import java.util.Locale;
/**
* These are the functions and variables that define the CannarySale objects, the CannarySale class.
*/
public class CannarySale extends HomeDeliverySale{
	
		/**
		 * Constructor of this class.
		 *
		 * @param bought Appliance that is bought.
		 */
		public CannarySale(Appliance bought){
			super(bought, 0.07*bought.getBasePrice());
		}
		
		/**
		 * Function that returns the ticket of a sale with information about the prices and discounts.
		 * @return Ticket string.
		 */
		@Override
		public String getTicket(){
			return "--------------------------------------------\n" +
				   super.soldProduct()+
				   "\n--------------------------------------------\n" +
				   super.bPrice()+
				   "Shipping cost: " + String.format(Locale.ROOT,"%17.2f",this.shipping) + " Euros\n"+
				   super.total(super.getPrice());
		}
}

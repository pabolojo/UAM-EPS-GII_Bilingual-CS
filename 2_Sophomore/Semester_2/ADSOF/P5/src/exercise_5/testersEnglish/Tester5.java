package exercise_5.testersEnglish;

import java.text.SimpleDateFormat;
import java.util.concurrent.TimeUnit;

import exercise_5.rules.TriggeredRule;

import java.text.ParseException;
import java.util.*;
/**
 * This is the Tester 5 class
 *
 */
public class Tester5 {

	/**
	 * The main method.
	 * 
	 * @param args array of input parameters
	 * @throws ParseException
	 */
	public static void main(String[] args) throws ParseException{
		SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy");
        Product p1 = new Product(10, sdf.parse("15/04/2020")); // “similar” to class Product of section 2
        TriggeredRule.<Product>trigRule("r1").trigger(p1, "price").when(
                pro -> Product.getDateDiff(Calendar.getInstance().getTime(), pro.getExpiration(), TimeUnit.DAYS) < 2)
                .exec(pro -> {
                    System.out.println("Beware! you are changing the price of a product that is about to expire ");
                });
        p1.setPrice(17);
    }

}


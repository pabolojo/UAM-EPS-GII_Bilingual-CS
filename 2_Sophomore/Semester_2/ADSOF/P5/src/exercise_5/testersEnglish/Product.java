package exercise_5.testersEnglish;

import java.util.*;
import java.util.concurrent.TimeUnit;

class Product extends Observable{ // A sample class to test the rules
    private double price;
    private Date expiration; // A better option is to use Calendar

    public Product(double p, Date date) {
        this.price = p;
        this.expiration = date;
    }

    public double getPrice() {
        return this.price;
    }

    public void setPrice(double p) {
        this.price = p;
        this.setChanged();
        this.notifyObservers("price");
    }

    public Date getExpiration() {
        return this.expiration;
    }

    public static long getDateDiff(Date date1, Date date2, TimeUnit timeUnit) {
        long diffInMillies = date2.getTime() - date1.getTime();
        return timeUnit.convert(diffInMillies, TimeUnit.MILLISECONDS);
    }

    @Override
    public String toString() {
        return this.price + ", expiration: " + this.expiration;
    }
}
package View.Views.Admin;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.util.Calendar;
import org.jdatepicker.impl.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import javax.swing.JFormattedTextField.AbstractFormatter;

import Controllers.Admin.ControllerAdminSettings;
import Model.App.Application;

import static Model.App.Application.INSTANCE;

/**
 * This Panel allows the admin to set the threshold and set the date
 *
 *
 */
public class PanelAdminSettings extends JPanel {
	private JLabel thresholdLabel = new JLabel(Integer.toString(INSTANCE.getThreshold()));

	private JLabel newthresholdLabel = new JLabel("New Threshold:");

	private JTextField threshold = new JTextField(20);

	private JButton bSetThreshold = new JButton("Set Threshold");
	private JButton bSignOut = new JButton("SignOut");
	private JButton bSetDate = new JButton("Change Date");

	UtilDateModel model = new UtilDateModel();
	JDatePanelImpl datePanel = new JDatePanelImpl(model, new Properties());
	JDatePickerImpl datePicker = new JDatePickerImpl(datePanel, new DateLabelFormatter());

	private ControllerAdminSettings controller;

	/**
	 * This is the constructor of the PanelAdminSettings that counts with a Field
	 * Text to introduce the Threshold and a calendar to select a new date in case
	 * the admin wanted to change it. Buttons are created to perform both
	 * functionalities and to exit the account.
	 */
	public PanelAdminSettings() {

		this.controller = new ControllerAdminSettings(this);
		this.setLayout(new BorderLayout());

		JPanel main = new JPanel();
		main.setLayout(new BoxLayout(main, BoxLayout.Y_AXIS));

		JPanel pn = new JPanel(new GridLayout(2, 2));
		pn.add(newthresholdLabel);
		pn.add(threshold);
		pn.add(new JLabel("Current Threshold:"));
		pn.add(thresholdLabel);

		JPanel pDate = new JPanel(new GridLayout(2, 1));
		pDate.add(new JLabel("Date:"));
		pDate.add(datePicker);

		main.add(pn);
		main.add(pDate);

		JPanel pb = new JPanel();
		pb.add(bSetThreshold);
		pb.add(bSetDate);
		pb.add(bSignOut);

		this.add(main, BorderLayout.NORTH);
		this.add(pb, BorderLayout.SOUTH);

		bSetThreshold.addActionListener(x -> setThreshold(x));
		bSignOut.addActionListener(x -> signOut(x));
		bSetDate.addActionListener(x -> setDate());
	}

	/**
	 * This method calls the method in the controller to set the date of the
	 * application
	 */
	private void setDate() {
		if (this.model.getValue() != null) {
			controller.setDate(this.model.getValue());
		}
	}

	/**
	 * This method calls the method in the controller to set the threshold
	 * 
	 * @param x select setThreshold button 
	 */
	public void setThreshold(ActionEvent x) {

		controller.bSetThreshold(this.threshold.getText());
		thresholdLabel.setText(Integer.toString(INSTANCE.getThreshold()));
		this.threshold.setText("");
	}

	/**
	 * This method calls the method in the controller to exit the logged account
	 * 
	 * @param x select signOut button
	 */
	public void signOut(ActionEvent x) {

		controller.bSignOut();
	}

	/**
	 * This class allows the representation of a calendar to make more easier the
	 * selection of a new date for the admin
	 * 
	 */
	public class DateLabelFormatter extends AbstractFormatter {

		private String datePattern = "yyyy-MM-dd";
		private SimpleDateFormat dateFormatter = new SimpleDateFormat(datePattern);

		@Override
		public Object stringToValue(String text) throws ParseException {
			return dateFormatter.parseObject(text);
		}

		@Override
		public String valueToString(Object value) throws ParseException {
			if (value != null) {
				Calendar cal = (Calendar) value;
				return dateFormatter.format(cal.getTime());
			} else {
				return Application.getDate().toString();
			}
		}

	}
}

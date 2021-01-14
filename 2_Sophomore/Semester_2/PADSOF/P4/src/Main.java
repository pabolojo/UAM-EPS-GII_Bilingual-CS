
import Model.App.Application;
import View.MainView;
import View.Views.*;
/**
 * This is the Main of the application , an basically calls the MainView with their parameters 
 *
 *
 */
public class Main {
	public static void main(String[] args) {
		Application model = Application.getApplication();
		MainView gui = MainView.getMainView(model.name, new PanelSignIn());
	}
}

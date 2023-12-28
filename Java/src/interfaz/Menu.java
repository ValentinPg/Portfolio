package interfaz;
import java.util.*;
import DBConnector.*;
public class Menu {
	
	public Menu() {
		options();
	}
	
	public int scan() {
		Scanner teclado = new Scanner(System.in);
		int n;
		
		do {
			n = teclado.nextInt();
		}while(valKey(n));
		
		return n;
	}
	
	public Boolean valKey(int n) {
		return (n < 0) || (n > 4);
	}
	
	public void options() {
		while(true) {
			System.out.println("\n Ingrese una opción:\n0-Salir\n1-Leer");
			switch(scan()) {
			case 0:
				System.out.println("\n\nGracias por usar el sistema"); 
				System.exit(0);
				break;
			case 1:
				subOptions();
				break;
			}
		}
	}
	
	public void subOptions() {
		System.out.println("\nDesea buscar por:\n1-Medicos\n2-Pacientes");
		String table;
		Connector con = new Connector();
		switch(scan()){
		case 1:
			table = "medicos";
			break;
		case 2:
			table = "pacientes";
			break;
		default:
			return;
		}
		con.print(con.searchAll(table));
	}
	
	
	
}

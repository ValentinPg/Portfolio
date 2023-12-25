package DBConnector;
import java.sql.*;
//En este archivo voy a desarrollar la clase para hacer la conexión con la base de datos en MySQL

public class Connector {
	
	private Connection miConector;
	
	public void main(String[] args) {
		try {
			this.miConector = DriverManager.getConnection("jdbc:mysql://localhost:3306/pruebas", "root", "1234");
		} catch (Exception e) {
			System.out.println("Error al conectar a la BD"); 
		}
	}

	public Connection getMiConector() {
		return miConector;
	}
	
	
	
	
}

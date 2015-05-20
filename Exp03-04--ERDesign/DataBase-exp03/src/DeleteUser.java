import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.*;

public class DeleteUser {
	private String username;
	private String password;
	
	public void setUsername(String username){
		this.username = new String(username);
	}
	public void setPassword(String password){
		this.password = new String(password);
	}
	
	Connection con;
	Statement st;
	public static Connection getConnection(){
		Connection con = null;
		try{
			Class.forName("com.mysql.jdbc.Driver");
			con = DriverManager.getConnection("jdbc:mysql://localhost:3306/social","root","agao0930yjc");
		}catch(Exception e){
			System.out.println("Connect Fail:"+e.getMessage());
		}
		return con;
	}
	
	public String execute() throws Exception{
		con = getConnection();
		try{
			String sql = "select * from user";
			st = (Statement)con.createStatement();
			ResultSet res = st.executeQuery(sql);
			boolean flag = false;
			while(res.next()){
				if(username.equals(res.getString("username")) && password.equals(res.getString("password"))){
					flag = true;
					break;
				}
			}
			if(flag){
				String sql2 = "delete from user where username='"+username+"'";
				int count = st.executeUpdate(sql2);
		//		System.out.println("Delete Success.Count: "+count);
				con.close();
				return "Success";
			}else{
				con.close();
		//		System.out.println("Delete Failed, Maybe No this Man.");
				return "Failed";
			}
		}catch(SQLException e){
		//	System.out.println("Update Failed.");
			return "Failed";
		}
	}
}
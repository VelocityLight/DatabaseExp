import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.*;

public class AlterUser {
	private String username;
	private String sex;
	private String birthday;
	private String address;
	private String password;
	
	public void setUsername(String username){
		this.username = new String(username);
	}
	public void setSex(String sex){
		this.sex = new String(sex);
	}
	public void setBirthday(String birthday){
		this.birthday = new String(birthday);
	}
	public void setAddress(String address){
		this.address = new String(address);
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
			boolean flag = false;
			String sql2="select * from user";
			st = (Statement)con.createStatement();
			ResultSet res = st.executeQuery(sql2);
			while(res.next()){
				if(username.equals(res.getString("username")) && password.equals(res.getString("password"))){
					flag = true;
					break;
				}
			}
			if(flag){
				String sql="update user set sex='"+sex+"',birthday='"+birthday+"',address='"+address+"',password='"+password+"' where username='"+username+"'";
		//		System.out.println(sql);
				int count = st.executeUpdate(sql);
		//		System.out.println("Update Successful.DataNum is:"+count);
				return "Success";
			}
			con.close();
		//	System.out.println("No this user");
			return "Failed";
		}catch(SQLException e){
		//	System.out.println("Update Failed.");
			return "Failed";
		}
	}
}
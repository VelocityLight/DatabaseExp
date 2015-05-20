import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.*;

public class AlterExperience {
	private String username;
	private String degree;
	private String school;
	private String working_place;
	
	public void setUsername(String username){
		this.username = new String(username);
	}
	public void setDegree(String degree){
		this.degree = new String(degree);
	}
	public void setSchool(String school){
		this.school = new String(school);
	}
	public void setWorking_place(String working_place){
		this.working_place = new String(working_place);
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
			String sql="update experience set degree='"+degree+"',school='"+school+"',working_place='"+working_place+"' where username='"+username+"'";
			st = (Statement)con.createStatement();
			System.out.println(sql);
			int count = st.executeUpdate(sql);
			System.out.println("Update Successful.DataNum is:"+count);
			con.close();
			return "Success";
		}catch(SQLException e){
			System.out.println("Update Failed.");
			return "Failed";
		}
	}
}
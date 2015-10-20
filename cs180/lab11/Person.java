

public class Person {
	private String fullName; //a person's full name
	private long phoneNumber; //a person's phone number
	private String email; //a person's email.
	
	public Person(String fullName, long phoneNumber, String email){
		this.fullName = fullName;
		this.phoneNumber = phoneNumber;
		this.email = email;
	}
	
	public String getName(){
		return fullName;
	}
	
	public long getNumber(){
		return phoneNumber;
	}
	
	public String getEmail(){
		return email;
	}
	
}

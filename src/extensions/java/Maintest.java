class Maintest
{
    public static void main(String[] args)
    {
	Genders gh = new Genders();
	System.out.println("Hello World");
	System.out.println("Handle Address = " + gh.ghaddr());
	System.out.println("NumNodes = " + gh.getnumnodes());
	System.out.println("Numattrs = " + gh.getnumattrs());
	System.out.println("Maxattrs = " + gh.getmaxattrs());
    }
}
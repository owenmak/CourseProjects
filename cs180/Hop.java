public class Hop {
  Hop() {
    System.out.println("Hop");
}
  public static void main(String []args) {
    Jump j = new Jump();
}
}
class Skip extends Hop {
  Skip() {
    System.out.println("Skip");
}
}
class Jump extends Skip {
  Jump() {
    System.out.println("Jump");
}
}
public class Die {
  public int roll() {
    return (int) (Math.random() * 5 + 1);
  }
}
class WeightedDie extends Die {
  @Override
  public int roll(){
    if (Math.random() < 0.5)
      return super.roll();
    else
      return 6;
  }
}
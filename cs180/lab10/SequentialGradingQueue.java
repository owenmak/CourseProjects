/**
 * This class implements a sequential grading queue where only one submission is run at a time. It can be instantiated
 * with the default constructor as follows:
 * 
 * SequentialGradingQueue queue = new SequentialGradingQueue();
 */
public class SequentialGradingQueue {

    /**
     * This method should use a Grader object to grade the submission with the gradeSubmission() method
     */
    public void addToQueue (Submission submission) {
      Grader grader = new Grader();
      grader.gradeSubmission(submission);
    }

}

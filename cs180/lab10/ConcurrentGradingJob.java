import java.util.concurrent.Semaphore;

/**
 * This class represents a grading job to be run concurrently with other jobs.
 */
public class ConcurrentGradingJob implements Runnable {
    private Submission submission;
    private Semaphore semaphore;
    /**
     * The constructor should store the submission and semaphore as private instance variables. These variables will
     * then be used in the run() method.
     */
    public ConcurrentGradingJob (Submission submission, Semaphore semaphore) {
      this.submission = submission;
      this.semaphore = semaphore;
    }

    /**
     * This method should first acquire a slot in the semaphore with its acquire() method. Then, it should use a Grader
     * object to grade the job's submission. Finally, it should release the semaphore slot with the release() method.
     */
    public void run () {
      try {
        semaphore.acquire();
        Grader grader = new Grader();
        grader.gradeSubmission(submission);
        semaphore.release();
      } catch (InterruptedException e) {
          return;
        }
    }

}

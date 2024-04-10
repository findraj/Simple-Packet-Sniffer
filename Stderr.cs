using System;

namespace IPK_2nd_project;

public class Stderr
{
  /// <summary>
  /// Function to write error message to stderr
  /// </summary>
  /// <param name="errorMessage">Text of the error message</param>
  public static void Write(string errorMessage = "There was an unknown error.")
  {
    Console.Error.WriteLine("ERR: " + errorMessage);
  }
}

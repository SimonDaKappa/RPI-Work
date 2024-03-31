package distributed;

// Import declarations generated by the SALSA compiler, do not modify.
import java.io.IOException;
import java.util.Vector;

import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.lang.reflect.InvocationTargetException;

import salsa.language.Actor;
import salsa.language.ActorReference;
import salsa.language.Message;
import salsa.language.RunTime;
import salsa.language.ServiceFactory;
import gc.WeakReference;
import salsa.language.Token;
import salsa.language.exceptions.*;
import salsa.language.exceptions.CurrentContinuationException;

import salsa.language.UniversalActor;

import salsa.naming.UAN;
import salsa.naming.UAL;
import salsa.naming.MalformedUALException;
import salsa.naming.MalformedUANException;

import salsa.resources.SystemService;

import salsa.resources.ActorService;

// End SALSA compiler generated import delcarations.

import java.util.*;
import java.util.Arrays;
import java.util.Collections;
import java.io.*;

public class worker extends UniversalActor  {
	public static void main(String args[]) {
		UAN uan = null;
		UAL ual = null;
		if (System.getProperty("uan") != null) {
			uan = new UAN( System.getProperty("uan") );
			ServiceFactory.getTheater();
			RunTime.receivedUniversalActor();
		}
		if (System.getProperty("ual") != null) {
			ual = new UAL( System.getProperty("ual") );

			if (uan == null) {
				System.err.println("Actor Creation Error:");
				System.err.println("	uan: " + uan);
				System.err.println("	ual: " + ual);
				System.err.println("	Identifier: " + System.getProperty("identifier"));
				System.err.println("	Cannot specify an actor to have a ual at runtime without a uan.");
				System.err.println("	To give an actor a specific ual at runtime, use the identifier system property.");
				System.exit(0);
			}
			RunTime.receivedUniversalActor();
		}
		if (System.getProperty("identifier") != null) {
			if (ual != null) {
				System.err.println("Actor Creation Error:");
				System.err.println("	uan: " + uan);
				System.err.println("	ual: " + ual);
				System.err.println("	Identifier: " + System.getProperty("identifier"));
				System.err.println("	Cannot specify an identifier and a ual with system properties when creating an actor.");
				System.exit(0);
			}
			ual = new UAL( ServiceFactory.getTheater().getLocation() + System.getProperty("identifier"));
		}
		RunTime.receivedMessage();
		worker instance = (worker)new worker(uan, ual,null).construct();
		gc.WeakReference instanceRef=new gc.WeakReference(uan,ual);
		{
			Object[] _arguments = { args };

			//preAct() for local actor creation
			//act() for remote actor creation
			if (ual != null && !ual.getLocation().equals(ServiceFactory.getTheater().getLocation())) {instance.send( new Message(instanceRef, instanceRef, "act", _arguments, false) );}
			else {instance.send( new Message(instanceRef, instanceRef, "preAct", _arguments, false) );}
		}
		RunTime.finishedProcessingMessage();
	}

	public static ActorReference getReferenceByName(UAN uan)	{ return new worker(false, uan); }
	public static ActorReference getReferenceByName(String uan)	{ return worker.getReferenceByName(new UAN(uan)); }
	public static ActorReference getReferenceByLocation(UAL ual)	{ return new worker(false, ual); }

	public static ActorReference getReferenceByLocation(String ual)	{ return worker.getReferenceByLocation(new UAL(ual)); }
	public worker(boolean o, UAN __uan)	{ super(false,__uan); }
	public worker(boolean o, UAL __ual)	{ super(false,__ual); }
	public worker(UAN __uan,UniversalActor.State sourceActor)	{ this(__uan, null, sourceActor); }
	public worker(UAL __ual,UniversalActor.State sourceActor)	{ this(null, __ual, sourceActor); }
	public worker(UniversalActor.State sourceActor)		{ this(null, null, sourceActor);  }
	public worker()		{  }
	public worker(UAN __uan, UAL __ual, Object obj) {
		//decide the type of sourceActor
		//if obj is null, the actor must be the startup actor.
		//if obj is an actorReference, this actor is created by a remote actor

		if (obj instanceof UniversalActor.State || obj==null) {
			  UniversalActor.State sourceActor;
			  if (obj!=null) { sourceActor=(UniversalActor.State) obj;}
			  else {sourceActor=null;}

			  //remote creation message sent to a remote system service.
			  if (__ual != null && !__ual.getLocation().equals(ServiceFactory.getTheater().getLocation())) {
			    WeakReference sourceRef;
			    if (sourceActor!=null && sourceActor.getUAL() != null) {sourceRef = new WeakReference(sourceActor.getUAN(),sourceActor.getUAL());}
			    else {sourceRef = null;}
			    if (sourceActor != null) {
			      if (__uan != null) {sourceActor.getActorMemory().getForwardList().putReference(__uan);}
			      else if (__ual!=null) {sourceActor.getActorMemory().getForwardList().putReference(__ual);}

			      //update the source of this actor reference
			      setSource(sourceActor.getUAN(), sourceActor.getUAL());
			      activateGC();
			    }
			    createRemotely(__uan, __ual, "distributed.worker", sourceRef);
			  }

			  // local creation
			  else {
			    State state = new State(__uan, __ual);

			    //assume the reference is weak
			    muteGC();

			    //the source actor is  the startup actor
			    if (sourceActor == null) {
			      state.getActorMemory().getInverseList().putInverseReference("rmsp://me");
			    }

			    //the souce actor is a normal actor
			    else if (sourceActor instanceof UniversalActor.State) {

			      // this reference is part of garbage collection
			      activateGC();

			      //update the source of this actor reference
			      setSource(sourceActor.getUAN(), sourceActor.getUAL());

			      /* Garbage collection registration:
			       * register 'this reference' in sourceActor's forward list @
			       * register 'this reference' in the forward acquaintance's inverse list
			       */
			      String inverseRefString=null;
			      if (sourceActor.getUAN()!=null) {inverseRefString=sourceActor.getUAN().toString();}
			      else if (sourceActor.getUAL()!=null) {inverseRefString=sourceActor.getUAL().toString();}
			      if (__uan != null) {sourceActor.getActorMemory().getForwardList().putReference(__uan);}
			      else if (__ual != null) {sourceActor.getActorMemory().getForwardList().putReference(__ual);}
			      else {sourceActor.getActorMemory().getForwardList().putReference(state.getUAL());}

			      //put the inverse reference information in the actormemory
			      if (inverseRefString!=null) state.getActorMemory().getInverseList().putInverseReference(inverseRefString);
			    }
			    state.updateSelf(this);
			    ServiceFactory.getNaming().setEntry(state.getUAN(), state.getUAL(), state);
			    if (getUAN() != null) ServiceFactory.getNaming().update(state.getUAN(), state.getUAL());
			  }
		}

		//creation invoked by a remote message
		else if (obj instanceof ActorReference) {
			  ActorReference sourceRef= (ActorReference) obj;
			  State state = new State(__uan, __ual);
			  muteGC();
			  state.getActorMemory().getInverseList().putInverseReference("rmsp://me");
			  if (sourceRef.getUAN() != null) {state.getActorMemory().getInverseList().putInverseReference(sourceRef.getUAN());}
			  else if (sourceRef.getUAL() != null) {state.getActorMemory().getInverseList().putInverseReference(sourceRef.getUAL());}
			  state.updateSelf(this);
			  ServiceFactory.getNaming().setEntry(state.getUAN(), state.getUAL(),state);
			  if (getUAN() != null) ServiceFactory.getNaming().update(state.getUAN(), state.getUAL());
		}
	}

	public UniversalActor construct() {
		Object[] __arguments = { };
		this.send( new Message(this, this, "construct", __arguments, null, null) );
		return this;
	}

	public class State extends UniversalActor .State {
		public worker self;
		public void updateSelf(ActorReference actorReference) {
			((worker)actorReference).setUAL(getUAL());
			((worker)actorReference).setUAN(getUAN());
			self = new worker(false,getUAL());
			self.setUAN(getUAN());
			self.setUAL(getUAL());
			self.activateGC();
		}

		public State() {
			this(null, null);
		}

		public State(UAN __uan, UAL __ual) {
			super(__uan, __ual);
			addClassName( "distributed.worker$State" );
			addMethodsForClasses();
		}

		public void construct() {}

		public void process(Message message) {
			Method[] matches = getMatches(message.getMethodName());
			Object returnValue = null;
			Exception exception = null;

			if (matches != null) {
				if (!message.getMethodName().equals("die")) {activateArgsGC(message);}
				for (int i = 0; i < matches.length; i++) {
					try {
						if (matches[i].getParameterTypes().length != message.getArguments().length) continue;
						returnValue = matches[i].invoke(this, message.getArguments());
					} catch (Exception e) {
						if (e.getCause() instanceof CurrentContinuationException) {
							sendGeneratedMessages();
							return;
						} else if (e instanceof InvocationTargetException) {
							sendGeneratedMessages();
							exception = (Exception)e.getCause();
							break;
						} else {
							continue;
						}
					}
					sendGeneratedMessages();
					currentMessage.resolveContinuations(returnValue);
					return;
				}
			}

			System.err.println("Message processing exception:");
			if (message.getSource() != null) {
				System.err.println("\tSent by: " + message.getSource().toString());
			} else System.err.println("\tSent by: unknown");
			System.err.println("\tReceived by actor: " + toString());
			System.err.println("\tMessage: " + message.toString());
			if (exception == null) {
				if (matches == null) {
					System.err.println("\tNo methods with the same name found.");
					return;
				}
				System.err.println("\tDid not match any of the following: ");
				for (int i = 0; i < matches.length; i++) {
					System.err.print("\t\tMethod: " + matches[i].getName() + "( ");
					Class[] parTypes = matches[i].getParameterTypes();
					for (int j = 0; j < parTypes.length; j++) {
						System.err.print(parTypes[j].getName() + " ");
					}
					System.err.println(")");
				}
			} else {
				System.err.println("\tThrew exception: " + exception);
				exception.printStackTrace();
			}
		}

		Integer tmp_val;
		Integer worker_id;
		ArrayList_I nodes;
		ArrayList_I degrees;
		ArrayList_S colors;
		ArrayList_I edge_sources;
		ArrayList_I edge_destinations;
		ArrayList_S uniqueColors;
		ArrayList_I uniqueColorCounts;
		ArrayList_I uniqueColorDegrees;
		ArrayList_I externalNodes;
		ArrayList_I externalNodeDegrees;
		worker[] workers;
		public void act_A(int id, Integer[] n, String[] c, Integer[] es, Integer[] ed) {
			tmp_val = 0;
			worker_id = id;
			nodes = new ArrayList_I(n);
			colors = new ArrayList_S(c);
			edge_sources = new ArrayList_I(es);
			edge_destinations = new ArrayList_I(ed);
			degrees = new ArrayList_I();
			for (int i = 0; i<nodes.list.size(); i++){
				degrees.list.add(0);
			}
			for (int i = 0; i<edge_sources.list.size(); i++){
				for (int j = 0; j<nodes.list.size(); j++){
					if (edge_sources.list.get(i).equals(nodes.list.get(j))) {{
						degrees.list.set(j, degrees.list.get(j)+1);
					}
}					if (edge_destinations.list.get(i).equals(nodes.list.get(j))) {{
						degrees.list.set(j, degrees.list.get(j)+1);
					}
}				}
			}
			uniqueColors = helper.getUniqueItems(colors);
			uniqueColorCounts = new ArrayList_I();
			for (int i = 0; i<uniqueColors.list.size(); i++){
				uniqueColorCounts.list.add(0);
			}
			for (int i = 0; i<uniqueColors.list.size(); i++){
				for (int j = 0; j<colors.list.size(); j++){
					if (uniqueColors.list.get(i).equals(colors.list.get(j))) {{
						uniqueColorCounts.list.set(i, uniqueColorCounts.list.get(i)+1);
					}
}				}
			}
			uniqueColorDegrees = new ArrayList_I();
			for (int i = 0; i<uniqueColors.list.size(); i++){
				uniqueColorDegrees.list.add(0);
			}
			for (int i = 0; i<uniqueColors.list.size(); i++){
				for (int j = 0; j<colors.list.size(); j++){
					if (uniqueColors.list.get(i).equals(colors.list.get(j))) {{
						uniqueColorDegrees.list.set(i, uniqueColorDegrees.list.get(i)+degrees.list.get(j));
					}
}				}
			}
			{
				// retA()
				{
					Object _arguments[] = {  };
					Message message = new Message( self, self, "retA", _arguments, null, currentMessage.getContinuationToken() );
					__messages.add( message );
				}
				throw new CurrentContinuationException();
			}
		}
		public Object[][] retA() {
			String[] returnColors = new String[uniqueColors.list.size()];
			Integer[] returnColorCounts = new Integer[uniqueColorCounts.list.size()];
			Integer[] returnColorDegrees = new Integer[uniqueColorDegrees.list.size()];
			for (int i = 0; i<uniqueColors.list.size(); i++){
				returnColors[i] = uniqueColors.list.get(i);
				returnColorCounts[i] = uniqueColorCounts.list.get(i);
				returnColorDegrees[i] = uniqueColorDegrees.list.get(i);
			}
			Object[][] ret = new Object[3][];
			ret[0] = returnColors;
			ret[1] = returnColorCounts;
			ret[2] = returnColorDegrees;
			return ret;
		}
		public void act_B() {
			Token x = new Token("x");
			{
				Token token_2_0 = new Token();
				// findExternalNodes()
				{
					Object _arguments[] = {  };
					Message message = new Message( self, self, "findExternalNodes", _arguments, null, token_2_0 );
					__messages.add( message );
				}
				// token x = findExternalNodeDegrees()
				{
					Object _arguments[] = {  };
					Message message = new Message( self, self, "findExternalNodeDegrees", _arguments, token_2_0, x );
					__messages.add( message );
				}
			}
			{
				// xret_B:((x))
				{
					Object _arguments[] = { x };
					Message message = new Message( self, self, "ret_B", _arguments, null, currentMessage.getContinuationToken() );
					Object[] _propertyInfo = { x };
					message.setProperty( "waitfor", _propertyInfo );
					__messages.add( message );
				}
				throw new CurrentContinuationException();
			}
		}
		public Integer[][] ret_B(Object in) {
			{
				// findMaxDegreeNodes()
				{
					Object _arguments[] = {  };
					Message message = new Message( self, self, "findMaxDegreeNodes", _arguments, null, currentMessage.getContinuationToken() );
					__messages.add( message );
				}
				throw new CurrentContinuationException();
			}
		}
		public Integer[][] findMaxDegreeNodes() {
			ArrayList_I maxDegreeNodes = new ArrayList_I();
			Integer maxDegree = 0;
			for (int i = 0; i<nodes.list.size(); i++){
				if (degrees.list.get(i)>maxDegree) {{
					maxDegree = degrees.list.get(i);
				}
}			}
			for (int i = 0; i<externalNodes.list.size(); i++){
				if (externalNodeDegrees.list.get(i)>maxDegree) {{
					maxDegree = externalNodeDegrees.list.get(i);
				}
}			}
			for (int i = 0; i<nodes.list.size(); i++){
				if (degrees.list.get(i).equals(maxDegree)) {{
					maxDegreeNodes.list.add(nodes.list.get(i));
				}
}			}
			for (int i = 0; i<externalNodes.list.size(); i++){
				if (externalNodeDegrees.list.get(i).equals(maxDegree)) {{
					maxDegreeNodes.list.add(externalNodes.list.get(i));
				}
}			}
			Integer[][] ret = new Integer[2][];
			ret[0] = maxDegreeNodes.list.toArray(new Integer[maxDegreeNodes.list.size()]);
			ret[1] = new Integer[1];
			ret[1][0] = maxDegree;
			return ret;
		}
		public void printExtNodesInfo() {
			{
				Token token_2_0 = new Token();
				// standardOutput<-println("Worker "+worker_id+" externalNodes = "+helper.printArr(externalNodes.list.toArray()))
				{
					Object _arguments[] = { "Worker "+worker_id+" externalNodes = "+helper.printArr(externalNodes.list.toArray()) };
					Message message = new Message( self, standardOutput, "println", _arguments, null, token_2_0 );
					__messages.add( message );
				}
				// standardOutput<-println("Worker "+worker_id+" externalNodeDegrees = "+helper.printArr(externalNodeDegrees.list.toArray()))
				{
					Object _arguments[] = { "Worker "+worker_id+" externalNodeDegrees = "+helper.printArr(externalNodeDegrees.list.toArray()) };
					Message message = new Message( self, standardOutput, "println", _arguments, token_2_0, null );
					__messages.add( message );
				}
			}
		}
		public void receiveWorkers(worker[] w) {
			workers = w;
		}
		public Integer getDegreeAtNode(Integer node, Integer requestor_id) {
			for (int i = 0; i<nodes.list.size(); i++){
				if (nodes.list.get(i).equals(node)) {{
					return degrees.list.get(i);
				}
}			}
			return 0;
		}
		public void findExternalNodes() {
			externalNodes = new ArrayList_I();
			for (int i = 0; i<edge_sources.list.size(); i++){
				if (!nodes.list.contains(edge_sources.list.get(i))) {{
					externalNodes.list.add(edge_sources.list.get(i));
				}
}				if (!nodes.list.contains(edge_destinations.list.get(i))) {{
					externalNodes.list.add(edge_destinations.list.get(i));
				}
}			}
		}
		public Boolean findExternalNodeDegrees() {
			externalNodeDegrees = new ArrayList_I();
			for (int i = 0; i<externalNodes.list.size(); i++){
				externalNodeDegrees.list.add(0);
				{
					Token token_3_0 = new Token();
					// join block
					token_3_0.setJoinDirector();
					for (int j = 0; j<workers.length; j++){
						if (j!=worker_id) {{
							{
								// workers[j]<-getDegreeAtNode(externalNodes.list.get(i), worker_id)
								{
									Object _arguments[] = { externalNodes.list.get(i), worker_id };
									Message message = new Message( self, workers[j], "getDegreeAtNode", _arguments, null, token_3_0 );
									__messages.add( message );
								}
							}
						}
}					}
					addJoinToken(token_3_0);
					// processDegreeResponses(token, i)
					{
						Object _arguments[] = { token_3_0, i };
						Message message = new Message( self, self, "processDegreeResponses", _arguments, token_3_0, null );
						__messages.add( message );
					}
				}
			}
			return true;
		}
		public void processDegreeResponses(Object[] tok, Integer i) {
			Integer sum = sumElements(tok);
			externalNodeDegrees.list.set(i, sum);
		}
		public void setTmpVal(Object val) {
			tmp_val = (Integer)val;
		}
		public Integer sumElements(Object[] arr) {
			Integer sum = 0;
			for (int i = 0; i<arr.length; i++){
				sum += ((Integer)arr[i]).intValue();
			}
			return sum;
		}
	}
}
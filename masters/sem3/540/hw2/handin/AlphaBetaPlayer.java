import java.util.Vector;
// CS 540 : HW2
// author: priyananda( shenoy@cs.wisc.edu )
// date: 5 Oct 2008
// random quote: [Fight Club] Tyler Durden: We're a generation of men raised by women.

/**
 * Basic Alpha Beta Pruning using iterative deepening.
 */
public class AlphaBetaPlayer extends CheckerPlayer implements CheckerBoardConstants
{
	public AlphaBetaPlayer(String name)
	{
		super(name);
	}
	//overridden method to compute the best next move
	public void calculateMove(int[][] bs, int whosTurn)
	{
		this.chosenMoveValue = Integer.MIN_VALUE;
		this.chosenMove = null;
		
		//iterative deepening. 100 is some arbitrary number which will never
		//be reached.
		for(int depth = 1 ; depth < 100 ; ++depth ){			
			//this finds best solution for the given depth cutoff and
			//stores it in tempSolution/tempValue
			findBestSolutionWithinDepth(bs, whosTurn, depth);			
			
			if(this.tempValue > this.chosenMoveValue){
				this.chosenMoveValue = this.tempValue;
				this.chosenMove = this.tempSolution;
			}
			if(Utils.debug)
				System.out.printf(
					"Done with depth limit %d\nI pruned the tree %d time(s)\n",
					depth, pruneCount
				);
		}
	}
	//depth-0 is always maximizing.
	private void findBestSolutionWithinDepth(int [][] bs,int whosTurn, int depth)
	{
		this.depthCutOff = depth;
		this.pruneCount = 0;
		
		this.tempSolution = null;
		this.tempValue = Integer.MIN_VALUE;
		
		for(Object m : Utils.getAllPossibleMoves(bs, whosTurn)){
			Move currentMove = (Move)m;
			int [][] bsnew = Utils.copyBoardState(bs);
			Utils.executeMove(whosTurn, currentMove, bsnew);
			int kidValue = alphaBetaPrune(
				bsnew,
				whosTurn,
				1, //initial depth
				Integer.MIN_VALUE, //alpha
				Integer.MAX_VALUE  //beta
			);
			if(this.tempSolution == null || kidValue > this.tempValue){
				this.tempSolution = currentMove;
				this.tempValue = kidValue;
			}
		}
	}
	//main method which implements alpha-beta minimax search
	private int alphaBetaPrune(int [][] bs,int whosTurn, int depth, int alpha, int beta)
	{
		if(depth >= this.depthCutOff)
			//reached the end of cutoff, stop
			return evaluateBoard(bs, whosTurn);
		
		//if i am a minimizing node, then the other player has to move.
		Vector kids = Utils.getAllPossibleMoves(bs,
			isMax(depth,whosTurn) ? whosTurn : otherPlayer(whosTurn)
		);
		if(kids.size() == 0)
			//this is a dead end. just return the current value.
			return evaluateBoard(bs, whosTurn);
		
		//is this node a max node or min node
		if(isMax(depth, whosTurn)){
			int i;
			for(i = 0 ; i < kids.size() && alpha < beta; ++i ){
				Move currentMove = (Move)kids.elementAt(i);
				int [][] bsnew = Utils.copyBoardState(bs);
				Utils.executeMove(whosTurn , currentMove, bsnew);
				int kidAlpha = alphaBetaPrune(bsnew,whosTurn,depth+1,alpha,beta);
				if( kidAlpha > alpha )
					alpha = kidAlpha;
			}
			pruneCount += kids.size() - i;
			return alpha;
		}else{
			int i;
			for(i = 0 ; i < kids.size() && alpha < beta; ++i ){
				Move currentMove = (Move)kids.elementAt(i);
				int [][] bsnew = Utils.copyBoardState(bs);
				
				//when the current node is minimizing, the other
				//player is to move.
				Utils.executeMove(
					otherPlayer(whosTurn),
					currentMove,
					bsnew
				);
				int kidBeta = alphaBetaPrune(bsnew, whosTurn,depth+1, alpha, beta);
				if( kidBeta < beta )
					beta = kidBeta;
			}
			pruneCount += kids.size() - i;
			return beta;
		}
	}
	
	private boolean isMax(int depth, int whosTurn)
	{
		if(depth % 2 == 0)
			//even depth is maximizing
			return true;
		else
			//odd depth is minimizing
			return false;
	}
	//this simplifies many things, like the current player always maximizes
	protected int evaluateBoard(int [][] bs,int whosTurn)
	{
		int ret = Utils.scoreCheckerBoard(bs, whosTurn);
		return (whosTurn == RED_PLAYER) ? ret : -ret;
	}
	//simple helper function to get the opposite player
	private int otherPlayer(int whosTurn)
	{
		return whosTurn == RED_PLAYER ? BLACK_PLAYER : RED_PLAYER; 
	}
	
	//best solution found so far
	private int chosenMoveValue = -1;
	//solution found for current depth iteration
	private Move tempSolution;
	private int tempValue;
	
	//now many nodes were pruned in current depth iteration
	private int pruneCount = 0;
	private int depthCutOff = 0;
}
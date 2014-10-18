package j3a.graphics;
import java.awt.*;
import java.awt.image.*;

public class Transparency
{
	public static Image makeColorTransparent(Image im)
	{
	    ImageFilter filter = new RGBImageFilter()
		{
			public final int filterRGB(int x, int y, int rgb)
			{
				if ( rgb == -16777216 )
					return 0;
				else
				  	return rgb;
			}
	    };
		BufferedImage bi = new BufferedImage(
			im.getWidth(null),im.getHeight(null),
			BufferedImage.TYPE_INT_ARGB
		);
		bi.createGraphics().drawImage(im,0,0,null );
        FilteredImageSource ip = new FilteredImageSource(
			bi.getSource(),
			filter
		);
		Image ret = Toolkit.getDefaultToolkit().createImage( ip );
		return ret;
    }
}